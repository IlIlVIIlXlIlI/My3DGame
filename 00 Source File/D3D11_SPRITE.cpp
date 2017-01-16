#include "D3D11_SPRITE.h"

SPRITE::SPRITE()
{
	m_Pos = D3DXVECTOR3(0, 0, 0);
	m_Scale = D3DXVECTOR3(1, 1, 1);
	
	
}

SPRITE::SPRITE(ID3D11DeviceContext* _pContext, LPSTR _texName, const int _WIN_WIDTH, const int _WIN_HEIGHT)
{
	m_Pos = D3DXVECTOR3(0, 0, 0);
	m_Scale = D3DXVECTOR3(1, 1, 1);
	m_Rot = 0.0f;
	Init(_pContext, _texName, _WIN_WIDTH, _WIN_HEIGHT);
}



HRESULT SPRITE::Init(ID3D11DeviceContext* _pContext,LPSTR _texName,const int _WIN_WIDTH,const int _WIN_HEIGHT)
{
	m_pDeviceContext = _pContext;
	m_pDeviceContext->GetDevice(&m_pDevice);
	
	
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_pDevice, _texName, nullptr, nullptr, &m_pTexture, nullptr)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	


	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob *pCompiledShader = nullptr;
	//バーテックスシェーダー作成
	if (FAILED(MakeShader("03 Shader File//Sprite2D.hlsl", "VS", "vs_5_0", (void**)&m_pVertexShader, &pCompiledShader))) return E_FAIL;
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(m_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return FALSE;
	}
	SAFE_RELEASE(pCompiledShader);
	//ピクセルシェーダー作成
	if (FAILED(MakeShader("03 Shader File//Sprite2D.hlsl", "PS", "ps_5_0", (void**)&m_pPixelShader, &pCompiledShader))) return E_FAIL;
	SAFE_RELEASE(pCompiledShader);
	//コンスタントバッファー作成　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SPRITE_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice->CreateBuffer(&cb, nullptr, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	//バーテックスバッファー作成
	if (FAILED(InitModel(_WIN_WIDTH,_WIN_HEIGHT)))
	{
		return E_FAIL;
	}
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState(&SamDesc, &m_pSampler);

	//テクスチャー読み込み
	return S_OK;
}

HRESULT SPRITE::InitModel(const int _WIN_WIDTH,const int _WIN_HEIGHT)
{
	//バーテックスバッファー作成
	//気をつけること。z値を１以上にしない。クリップ空間でz=1は最も奥を意味する。したがって描画されない。
	SpriteVertex vertices[] =
	{
		D3DXVECTOR3(0,0,0),D3DXVECTOR2(0,0),//頂点1,
		D3DXVECTOR3(_WIN_WIDTH,0,0), D3DXVECTOR2(1,0),//頂点2
		D3DXVECTOR3(0,_WIN_HEIGHT,0),D3DXVECTOR2(0,1), //頂点3
		D3DXVECTOR3(_WIN_WIDTH,_WIN_HEIGHT,0),D3DXVECTOR2(1,1), //頂点4
	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SpriteVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}
	

	return S_OK;
}
//
HRESULT SPRITE::MakeShader(LPSTR _szFileName, LPSTR _szFuncName, LPSTR _szProfileName, void** _ppShader, ID3DBlob** _ppBlob)
{
	ID3DBlob *pErrors = nullptr;
	if (FAILED(D3DX11CompileFromFileA(_szFileName, nullptr, nullptr, _szFuncName, _szProfileName, D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, _ppBlob, &pErrors, nullptr)))
	{
		char*p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	char szProfile[3] = { 0 };
	memcpy(szProfile, _szProfileName, 2);
	if (strcmp(szProfile, "vs") == 0)//Vertex Shader
	{
		if (FAILED(m_pDevice->CreateVertexShader((*_ppBlob)->GetBufferPointer(), (*_ppBlob)->GetBufferSize(), nullptr, (ID3D11VertexShader**)_ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "ps") == 0)//Pixel Shader
	{
		if (FAILED(m_pDevice->CreatePixelShader((*_ppBlob)->GetBufferPointer(), (*_ppBlob)->GetBufferSize(), nullptr, (ID3D11PixelShader**)_ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "gs") == 0)//Geometry Shader
	{
		if (FAILED(m_pDevice->CreateGeometryShader((*_ppBlob)->GetBufferPointer(), (*_ppBlob)->GetBufferSize(), nullptr, (ID3D11GeometryShader**)_ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "hs") == 0)//Hull Shader
	{
		if (FAILED(m_pDevice->CreateHullShader((*_ppBlob)->GetBufferPointer(), (*_ppBlob)->GetBufferSize(), nullptr, (ID3D11HullShader**)_ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "ds") == 0)//Domain Shader
	{
		if (FAILED(m_pDevice->CreateDomainShader((*_ppBlob)->GetBufferPointer(), (*_ppBlob)->GetBufferSize(), nullptr, (ID3D11DomainShader**)_ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "cs") == 0)//Compute Shader
	{
		if (FAILED(m_pDevice->CreateComputeShader((*_ppBlob)->GetBufferPointer(), (*_ppBlob)->GetBufferSize(), nullptr, (ID3D11ComputeShader**)_ppShader))) return E_FAIL;
	}
	return S_OK;
}


void SPRITE::Render(D3DXVECTOR3 _Pos,float _Scale)
{
	m_Pos = _Pos;
	m_Scale = D3DXVECTOR3(_Scale, _Scale, _Scale);

	//プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//使用するシェーダーのセット
	m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

	//このコンスタントバッファーを使うシェーダーの登録
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	
	//テクスチャーをシェーダーに渡す
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);



	D3DXMATRIX World;
	//ワールドトランスフォーム
	D3DXMatrixRotationZ(&mRot, m_Rot);
	D3DXMatrixTranslation(&mTran, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&mScale, m_Scale.x, m_Scale.y, m_Scale.z);
	World = mScale * mRot * mTran;
	
	

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	SPRITE_CONSTANT_BUFFER cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド行列を渡す
		cb.mW = World ;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);
		//ビューポートサイズを渡す（クライアント領域の横と縦）
		cb.ViewPortWidth = WINDOW_WIDTH;
		cb.ViewPortHeight = WINDOW_HEIGHT;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}


	//バーテックスバッファーをセット
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);


	//プリミティブをレンダリング
	m_pDeviceContext->Draw(4, 0);
}

void SPRITE::DestroyD3D()
{
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
}
