#include "PARTICLE.h"

PARTICLE::PARTICLE()
{

}


PARTICLE::PARTICLE(int _MaxParticle, D3DXVECTOR3& _EmitPos)
{
	ZeroMemory(this, sizeof(PARTICLE));


	m_MaxParticle = _MaxParticle;
	m_EmitPos = _EmitPos;
	pPartArray = new PART[m_MaxParticle];

	for (int i = 0; i<m_MaxParticle; i++)
	{
		pPartArray[i].Pos = _EmitPos;
		pPartArray[i].Dir = D3DXVECTOR3(2 * ((float)rand() / (float)RAND_MAX) - 1, (float)rand() / (float)RAND_MAX, 2 * ((float)rand() / (float)RAND_MAX) - 1);
		D3DXVec3Normalize(&pPartArray[i].Dir, &pPartArray[i].Dir);
		pPartArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX))*0.00001;
		pPartArray[i].BirthFrame = rand();
	}
}
PARTICLE::~PARTICLE()
{
	DestroyD3D();
}
void PARTICLE::Run()
{
	m_Frame++;
	for (int i = 0; i<m_MaxParticle; i++)
	{
		if (m_Frame>pPartArray[i].BirthFrame)
		{
			pPartArray[i].Pos += pPartArray[i].Dir*pPartArray[i].Speed;
			//重力
			pPartArray[i].Dir += D3DXVECTOR3(0, -0.0000098, 0);
			//地面でのバウンド

		}
	}
}
D3DXVECTOR3& PARTICLE::GetParticlePos(int _Index)
{
	return pPartArray[_Index].Pos;
}

HRESULT PARTICLE::Init(ID3D11DeviceContext* _pContext)
{
	m_pDeviceContext = _pContext;
	m_pDeviceContext->GetDevice(&m_pDevice);

	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob *pCompiledShader = NULL;
	//バーテックスシェーダー作成
	if (FAILED(MakeShader("PointSprite3D_Tex.hlsl", "VS", "vs_5_0", (void**)&m_pVertexShader, &pCompiledShader))) return E_FAIL;
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(m_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return FALSE;
	}
	SAFE_RELEASE(pCompiledShader);
	//ジオメトリシェーダー作成
	if (FAILED(MakeShader("PointSprite3D_Tex.hlsl", "GS", "gs_5_0", (void**)&m_pGeometryShader, &pCompiledShader))) return E_FAIL;
	SAFE_RELEASE(pCompiledShader);
	//ピクセルシェーダー作成
	if (FAILED(MakeShader("PointSprite3D_Tex.hlsl", "PS", "ps_5_0", (void**)&m_pPixelShader, &pCompiledShader))) return E_FAIL;
	SAFE_RELEASE(pCompiledShader);
	//コンスタントバッファー作成　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(PARTICLE_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	//点としてのバーテックスバッファー作成
	if (FAILED(InitModel()))
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
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_pDevice, "particle.png", NULL, NULL, &m_pTexture, NULL)))
	{
		MessageBoxA(0, "テクスチャーを読み込めません", "", MB_OK);
		return E_FAIL;
	}
	

	//パーティクル初期化
	m_pParticle = new PARTICLE(500, D3DXVECTOR3(0, 0, 0));

	return S_OK;
}
HRESULT PARTICLE::MakeShader(LPSTR szFileName, LPSTR szFuncName, LPSTR szProfileName, void** ppShader, ID3DBlob** ppBlob)
{
	ID3DBlob *pErrors = NULL;
	if (FAILED(D3DX11CompileFromFileA(szFileName, NULL, NULL, szFuncName, szProfileName, D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, NULL, ppBlob, &pErrors, NULL)))
	{
		char*p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	char szProfile[3] = { 0 };
	memcpy(szProfile, szProfileName, 2);
	if (strcmp(szProfile, "vs") == 0)//Vertex Shader
	{
		if (FAILED(m_pDevice->CreateVertexShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11VertexShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "ps") == 0)//Pixel Shader
	{
		if (FAILED(m_pDevice->CreatePixelShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11PixelShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "gs") == 0)//Geometry Shader
	{
		if (FAILED(m_pDevice->CreateGeometryShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11GeometryShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "hs") == 0)//Hull Shader
	{
		if (FAILED(m_pDevice->CreateHullShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11HullShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "ds") == 0)//Domain Shader
	{
		if (FAILED(m_pDevice->CreateDomainShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11DomainShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "cs") == 0)//Compute Shader
	{
		if (FAILED(m_pDevice->CreateComputeShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11ComputeShader**)ppShader))) return E_FAIL;
	}
	return S_OK;
}

HRESULT  PARTICLE::InitModel()
{
	//バーテックスバッファー作成
	PARTICLE_Vertex vertices[] =
	{
		D3DXVECTOR3(-0.5f, 0.5f, 0.0f),
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PARTICLE_Vertex) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}
	//バーテックスバッファーをセット
	UINT stride = sizeof(PARTICLE_Vertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	return S_OK;
}



void     PARTICLE::Render()
{
	//プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//使用するシェーダーのセット
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->GSSetShader(m_pGeometryShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	//このコンスタントバッファーをどのシェーダーで使うか
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//テクスチャーをシェーダーに渡す
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);


	D3DXMATRIX World;
	D3DXMATRIX View;
	D3DXMATRIX Proj;
	D3DXMATRIX WVP;
	//パーティクル１粒を１枚ポイントスプライトとして５００枚描画
	for (int i = 0; i<500; i++)
	{
		//ワールドトランスフォームは個々で異なる
		D3DXMATRIX Scale, Tran;
		D3DXMatrixScaling(&Scale, 0.001, 0.001, 0.001);
		D3DXVECTOR3 ParticlePos = m_pParticle->GetParticlePos(i);
		D3DXMatrixTranslation(&Tran, ParticlePos.x, ParticlePos.y, ParticlePos.z);
		World = Scale*Tran;

		WVP = World*View*Proj;

		D3D11_MAPPED_SUBRESOURCE pData;
		PARTICLE_CONSTANT_BUFFER cb;
		if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			//ワールド、カメラ、射影行列を渡す
			D3DXMATRIX m = WVP;
			D3DXMatrixTranspose(&m, &m);
			cb.mWVP = WVP;

			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
			m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
		}
	}
	D3DXVECTOR3 ParticlePos = m_pParticle->GetParticlePos(7);



	
	//プリミティブをレンダリング
	m_pDeviceContext->Draw(1, 0);
	//パーティクルのアニメを進める

	
	m_pParticle->Run();
	
}
void	 PARTICLE::DestroyD3D()
{

}