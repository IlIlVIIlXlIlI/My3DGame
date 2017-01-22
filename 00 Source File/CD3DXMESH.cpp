#include "CD3DXMESH.h"

CD3DXMESH::CD3DXMESH(HWND _hWnd, ID3D11Device* _pDevice11, ID3D11DeviceContext* _pContext11, LPSTR _FileName)
{
	ZeroMemory(this,sizeof(CD3DXMESH));

	m_Pos = D3DXVECTOR3(0, 0, 0);				//初期位置
	m_fScale=1.0f;								//初期スケール

	D3DXVECTOR3 ToVec = D3DXVECTOR3(0, 0, 0);

	/*初期化*/
	Init(_hWnd,_pDevice11,_pContext11,_FileName);
}
//
CD3DXMESH::CD3DXMESH()
{
	ZeroMemory(this, sizeof(CD3DXMESH));
	m_fScale = 1.0f;
	D3DXVECTOR3 ToVec = D3DXVECTOR3(0, 0, 0);
}
//
CD3DXMESH::~CD3DXMESH()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pDevice9);
	SAFE_RELEASE(m_pD3d9);
}
//
//======================================================================================
//頂点3つとUV座標３つと法線をもとに接線を計算する。返す4次元ベクトルのwは左か右手系かの判断用フラグ。
//======================================================================================
D3DXVECTOR4 CalcTangent(D3DXVECTOR3 v1, D3DXVECTOR3 v2,D3DXVECTOR3 v3,
						D3DXVECTOR2 uv1,D3DXVECTOR2 uv2,D3DXVECTOR2 uv3,D3DXVECTOR3 normal)
{
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 bitangent;

	D3DXVECTOR3 edge1=v2-v1;
	D3DXVECTOR3 edge2=v3-v1;
	D3DXVec3Normalize(&edge1,&edge1);
	D3DXVec3Normalize(&edge2,&edge2);
	D3DXVECTOR2 uvEdge1=uv2-uv1;
	D3DXVECTOR2 uvEdge2=uv3-uv1;
	D3DXVec2Normalize(&uvEdge1,&uvEdge1);
	D3DXVec2Normalize(&uvEdge2,&uvEdge2);

	float det=(uvEdge1.x*uvEdge2.y)-(uvEdge1.y*uvEdge2.x);
	det=1.0f/det;

	tangent.x=(uvEdge2.y*edge1.x-uvEdge1.y*edge2.x)*det;
	tangent.y=(uvEdge2.y*edge1.y-uvEdge1.y*edge2.y)*det;
	tangent.z=(uvEdge2.y*edge1.z-uvEdge1.y*edge2.z)*det;

	bitangent.x=(-uvEdge2.x*edge1.x+uvEdge1.x*edge2.x)*det;
	bitangent.y=(-uvEdge2.x*edge1.y+uvEdge1.x*edge2.y)*det;
	bitangent.z=(-uvEdge2.x*edge1.z+uvEdge1.x*edge2.z)*det;

	D3DXVec3Normalize(&tangent,&tangent);
	D3DXVec3Normalize(&bitangent,&bitangent);

	D3DXVECTOR3 BiNormal;
	D3DXVec3Cross(&BiNormal,&normal,&tangent);

	float w=(D3DXVec3Dot(&BiNormal,&bitangent)>=0.0f) ? 1.0f : -1.0f;

	return D3DXVECTOR4(tangent.x,tangent.y,tangent.z, w);
}
//
HRESULT CD3DXMESH::Init(HWND _hWnd,ID3D11Device* _pDevice11,ID3D11DeviceContext* _pContext11,LPSTR _FileName)
{
	m_hWnd=_hWnd;
	m_pDevice11=_pDevice11;
	m_pDeviceContext11=_pContext11;

	if(FAILED(InitDx9()))
	{
		return E_FAIL;
	}
	if(FAILED(LoadXMesh(_FileName)))
	{
		return E_FAIL;
	}

	if(FAILED(InitShader()))
	{
		return E_FAIL;
	}
	
	//ノーマルマップ用テクスチャーを読み込む
	//LoadNomalMap("Rock_SharpStainedCliff_2k_n.png", m_pNormalTexture);

	return S_OK;
}
//

//
HRESULT CD3DXMESH::Init(HWND _hWnd, ID3D11Device* _pDevice11, ID3D11DeviceContext* _pContext11,
	LPSTR _FileName,LPSTR _NomalMap)
{
	m_hWnd = _hWnd;
	m_pDevice11 = _pDevice11;
	m_pDeviceContext11 = _pContext11;

	if (FAILED(InitDx9()))
	{
		return E_FAIL;
	}
	if (FAILED(LoadXMesh(_FileName)))
	{
		return E_FAIL;
	}

	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}

	//ノーマルマップ用テクスチャーを読み込む
	LoadNomalMap(_NomalMap, m_pNormalTexture);

	return S_OK;
}

//"Rock_SharpStainedCliff_2k_n.png"
//======================================================================================
//D3DXのパーサーを使うためには、Dx9のデバイスが必要なので作成する。
//======================================================================================
HRESULT CD3DXMESH::InitDx9()
{
	// 「Direct3D」オブジェクトの作成
	if( nullptr == ( m_pD3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		MessageBoxA(0,"Direct3D9の作成に失敗しました","",MB_OK);
		return E_FAIL;
	}
	// 「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferFormat =D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount=1;	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	

	if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
									  D3DCREATE_HARDWARE_VERTEXPROCESSING,
									  &d3dpp, &m_pDevice9 ) ) )
	{
		if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
									  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									  &d3dpp, &m_pDevice9 ) ) )
		{
			MessageBoxA(0,"HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します",nullptr,MB_OK);
			if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
									  D3DCREATE_HARDWARE_VERTEXPROCESSING,
									  &d3dpp, &m_pDevice9 ) ) )
			{
				if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
									  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									  &d3dpp, &m_pDevice9 ) ) )
				{
					MessageBoxA(0,"DIRECT3Dデバイスの作成に失敗しました",nullptr,MB_OK);
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}
//
//======================================================================================
// Xファイルからメッシュをロードする
//======================================================================================
HRESULT CD3DXMESH::LoadXMesh(LPSTR _FileName)
{
	LPD3DXBUFFER pD3DXMtrlBuffer = nullptr;

	if (FAILED(D3DXLoadMeshFromXA(_FileName, D3DXMESH_SYSTEMMEM | D3DXMESH_32BIT,
		m_pDevice9, nullptr, &pD3DXMtrlBuffer, nullptr,
		&m_dwNumMaterial, &m_pMesh)))
	{
		assert("Xファイルの読み込み失敗");
		MessageBoxA(nullptr, "Xファイルの読み込みに失敗しました", nullptr, MB_OK);
		return E_FAIL;
	}

	//この時点で、ファイルから取り出したメッシュデータが、Dx9のD3DXメッシュに入っている、
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	//あとは、そこから好きな情報を取り出してDx11の自前メッシュに利用するだけ。
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterial = new MY_MATERIAL[m_dwNumMaterial];
	m_ppIndexBuffer=new ID3D11Buffer*[m_dwNumMaterial];

	for( DWORD i=0; i<m_dwNumMaterial; i++ )
	{
		//アンビエント
		m_pMaterial[i].Ambient.x=d3dxMaterials[i].MatD3D.Ambient.r;
		m_pMaterial[i].Ambient.y=d3dxMaterials[i].MatD3D.Ambient.g;
		m_pMaterial[i].Ambient.z=d3dxMaterials[i].MatD3D.Ambient.b;
		m_pMaterial[i].Ambient.w=d3dxMaterials[i].MatD3D.Ambient.a;
		//ディフューズ
		m_pMaterial[i].Diffuse.x=d3dxMaterials[i].MatD3D.Diffuse.r;
		m_pMaterial[i].Diffuse.y=d3dxMaterials[i].MatD3D.Diffuse.g;
		m_pMaterial[i].Diffuse.z=d3dxMaterials[i].MatD3D.Diffuse.b;
		m_pMaterial[i].Diffuse.w=d3dxMaterials[i].MatD3D.Diffuse.a;
		//スペキュラー
		m_pMaterial[i].Specular.x=d3dxMaterials[i].MatD3D.Specular.r;
		m_pMaterial[i].Specular.y=d3dxMaterials[i].MatD3D.Specular.g;
		m_pMaterial[i].Specular.z=d3dxMaterials[i].MatD3D.Specular.b;
		m_pMaterial[i].Specular.w=d3dxMaterials[i].MatD3D.Specular.a;
		//テクスチャーがあれば
		if( d3dxMaterials[i].pTextureFilename != nullptr && 
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0 )
		{
			m_Texture=true;
			strcpy(m_pMaterial[i].szTextureName,d3dxMaterials[i].pTextureFilename);
			//テクスチャーを作成
			if(FAILED(D3DX11CreateShaderResourceViewFromFileA(m_pDevice11,
				m_pMaterial[i].szTextureName, nullptr, nullptr, &m_pMaterial[i].pTexture, nullptr )))
			{
				return E_FAIL;
			}
		}
	}

	//インデックスバッファーを作成

	//メッシュの属性情報を得る。属性情報でインデックスバッファーから細かいマテリアルごとのインデックスバッファを分離できる
	D3DXATTRIBUTERANGE* pAttrTable=nullptr;
	
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,0,0,0,0);
	m_pMesh->GetAttributeTable(nullptr,&m_NumAttr);
	pAttrTable= new D3DXATTRIBUTERANGE[m_NumAttr];
	if(FAILED(m_pMesh->GetAttributeTable(pAttrTable,&m_NumAttr)))
	{
		MessageBoxA(0,"属性テーブル取得失敗","",MB_OK);
		return E_FAIL;
	}
	//D3DXMESHの場合、ロックしないとD3DXインデックスバッファーから取り出せないのでロックする。
	int* pIndex=nullptr;
	m_pMesh->LockIndexBuffer(D3DLOCK_READONLY,(void**)&pIndex);

	//属性ごとのインデックスバッファを作成
	for(DWORD i=0;i<m_NumAttr;i++)
	{
		m_AttrID[i]=pAttrTable[i].AttribId;
		//Dx9のD3DMESHのインデックスバッファーからの情報で、Dx11のインデックスバッファを作成
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( int ) * pAttrTable[i].FaceCount*3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
	
		InitData.pSysMem = &pIndex[pAttrTable[i].FaceStart*3];//大きいインデックスバッファ内のオフセット(*3を忘れずに）

		if( FAILED( m_pDevice11->CreateBuffer( &bd, &InitData, &m_ppIndexBuffer[i] ) ) )
		{
			return FALSE;
		}
		m_pMaterial[m_AttrID[i]].dwNumFace=pAttrTable[i].FaceCount;
	}
	delete[] pAttrTable;
	m_pMesh->UnlockIndexBuffer();

	pD3DXMtrlBuffer->Release();

	//バーテックスバッファーを作成
	
	//D3DXMESHの場合、ロックしないとD3DXバーテックスバッファーから取り出せないのでロックする。
	DWORD NumVertices = m_pMesh->GetNumVertices();
	LPDIRECT3DVERTEXBUFFER9 pVB=nullptr;
	m_pMesh->GetVertexBuffer(&pVB);
	DWORD dwStride = sizeof(MY_VERTEX);
	MY_VERTEX* pMyVertex = new MY_VERTEX[NumVertices];
	BYTE *pVertices = nullptr;
	if(SUCCEEDED(pVB->Lock(0,0,(VOID**)&pVertices,0)))
	{
		X_VERTEX* pXVertices = (X_VERTEX*)pVertices;
		
		for (DWORD i = 0; i<NumVertices; i++)
		{
			//接線成分以外はXファイルのデータからコピー
			pMyVertex[i].vPos = pXVertices[i].vPos;
			pMyVertex[i].vNorm = pXVertices[i].vNorm;
			pMyVertex[i].vTex = pXVertices[i].vTex;
		}

		//テクスチャー座標がマイナス対策
		if(m_Texture)
		{
			for(int i=0;i<m_pMesh->GetNumVertices();i++)
			{
				if(pMyVertex[i].vTex.x<0)
				{
					pMyVertex[i].vTex.x+=1;
				}
				if(pMyVertex[i].vTex.y<0)
				{
					pMyVertex[i].vTex.y+=1;
				}
			}
		}

		

		pVB->Unlock();
	}

	//まだ接線が無い。ここで作成し、追加
	m_pMesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&pIndex);
	for (int i = 0; i<m_pMesh->GetNumFaces(); i++)
	{
		D3DXVECTOR3 v1 = pMyVertex[pIndex[i * 3]].vPos;
		D3DXVECTOR3 v2 = pMyVertex[pIndex[i * 3 + 1]].vPos;
		D3DXVECTOR3 v3 = pMyVertex[pIndex[i * 3 + 2]].vPos;

		D3DXVECTOR2 t1 = pMyVertex[pIndex[i * 3]].vTex;
		D3DXVECTOR2 t2 = pMyVertex[pIndex[i * 3 + 1]].vTex;
		D3DXVECTOR2 t3 = pMyVertex[pIndex[i * 3 + 2]].vTex;

		D3DXVECTOR3 vN = (pMyVertex[pIndex[i * 3]].vNorm + pMyVertex[pIndex[i * 3 + 1]].vNorm + pMyVertex[pIndex[i * 3 + 2]].vNorm) / 3;
		D3DXVECTOR4 vTangent;

		vTangent = CalcTangent(v1, v2, v3, t1, t2, t3, vN);

		pMyVertex[pIndex[i * 3]].vTangent = vTangent;
		pMyVertex[pIndex[i * 3 + 1]].vTangent = vTangent;
		pMyVertex[pIndex[i * 3 + 2]].vTangent = vTangent;
	}
	m_pMesh->UnlockIndexBuffer();

	//Dx9のD3DMESHのバーテックスバッファーからの情報で、Dx11のバーテックスバッファを作成
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = dwStride*NumVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = pMyVertex;
	if (FAILED(m_pDevice11->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
		return FALSE;

	SAFE_RELEASE( pVB );

	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc,sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice11->CreateSamplerState( &SamDesc, &m_pSampleLinear);

	

	return S_OK;
}
//
//
//
HRESULT CD3DXMESH::InitShader()
{
	SetShaderDirectory();
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3D10Blob *pCompiledShader=nullptr;
	ID3D10Blob *pErrors=nullptr;
	//ブロブからバーテックスシェーダー作成
	if(m_Texture)
	{
		if(FAILED(D3DX11CompileFromFile("MESH.hlsl",nullptr,nullptr,"VS","vs_5_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
		{
			MessageBox(0,"hlsl読み込み失敗",nullptr,MB_OK);
			return E_FAIL;
		}
	}
	else
	{
		if(FAILED(D3DX11CompileFromFile("MESH.hlsl",nullptr,nullptr,"VS_NoTeX","vs_5_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
		{
			MessageBox(0,"hlsl読み込み失敗",nullptr,MB_OK);
			return E_FAIL;
		}
	}
	SAFE_RELEASE(pErrors);

	if(FAILED(m_pDevice11->CreateVertexShader(pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),nullptr,&m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0,"バーテックスシェーダー作成失敗(CD3DXMESH)",nullptr,MB_OK);
		return E_FAIL;
	}
	//頂点インプットレイアウトを定義
	UINT numElements=0;
	D3D11_INPUT_ELEMENT_DESC layout[4];
	if(m_Texture)
	{
		D3D11_INPUT_ELEMENT_DESC tmp[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		numElements=4;
		memcpy(layout,tmp,sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);
	}
	else
	{
		D3D11_INPUT_ELEMENT_DESC tmp[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },			
		};
		numElements=2;
		memcpy(layout,tmp,sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);
	}

	//頂点インプットレイアウトを作成
	if( FAILED( m_pDevice11->CreateInputLayout( layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout ) ) )
	{
		return FALSE;
	}
	//ブロブからピクセルシェーダー作成
	if(m_Texture)
	{
		if(FAILED(D3DX11CompileFromFile("MESH.hlsl",nullptr,nullptr,"PS","ps_4_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
		{
			MessageBox(0,"hlsl読み込み失敗",nullptr,MB_OK);
			return E_FAIL;
		}
	}
	else
	{
		if(FAILED(D3DX11CompileFromFile("MESH.hlsl",nullptr,nullptr,"PS_NoTex","ps_4_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
		{
			MessageBox(0,"hlsl読み込み失敗",nullptr,MB_OK);
			return E_FAIL;
		}
	}
	SAFE_RELEASE(pErrors);
	if(FAILED(m_pDevice11->CreatePixelShader(pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),nullptr,&m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0,"ピクセルシェーダー作成失敗",nullptr,MB_OK);
		return E_FAIL;
	}


	SAFE_RELEASE(pCompiledShader);
	//コンスタントバッファー作成　変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLECONSTANT_BUFFER0);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice11->CreateBuffer(&cb, nullptr, &m_pConstantBuffer0)))
	{
		return E_FAIL;
	}
	//コンスタントバッファー作成  マテリアル渡し用
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLECONSTANT_BUFFER1);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice11->CreateBuffer(&cb, nullptr, &m_pConstantBuffer1)))
	{
		return E_FAIL;
	}





	return S_OK;
}
//
//
//
void CD3DXMESH::Render(D3DXMATRIX& _mView,D3DXMATRIX& _mProj,D3DXVECTOR3& _vLight,D3DXVECTOR3& _vEye)
{
	//ワールドトランスフォーム（絶対座標変換）
	D3DXMatrixScaling(&mScale,m_fScale,m_fScale,m_fScale);
	D3DXMatrixRotationY(&mYaw,m_fYaw);
	D3DXMatrixRotationX(&mPitch,m_fPitch);
	D3DXMatrixRotationZ(&mRoll,m_fRoll);
	
	D3DXMatrixTranslation(&mTran,m_Pos.x,m_Pos.y,m_Pos.z);

	mWorld=mScale*mYaw*mPitch*mRoll*mTran;
	
	
	//使用するシェーダーの登録
	m_pDeviceContext11->VSSetShader(m_pVertexShader,nullptr,0);
	m_pDeviceContext11->PSSetShader(m_pPixelShader,nullptr,0);

	
	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(m_pDeviceContext11->Map(m_pConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SIMPLECONSTANT_BUFFER0 sg;
		//ワールド行列を渡す
		sg.mW = mWorld;
		D3DXMatrixTranspose(&sg.mW, &sg.mW);
		//ワールドの逆の転置行列を渡す
		D3DXMatrixInverse(&sg.mWIT, nullptr, &mWorld);//この場合、転置を渡したい場合は、転置しなければいい
												   //ワールド、カメラ、射影行列を渡す
		sg.mWVP = mWorld*_mView*_mProj;
		D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
		//ライトの方向を渡す
		sg.vLightDir = D3DXVECTOR4(_vLight.x, _vLight.y, _vLight.z, 0.0f);
		//視点位置を渡す
		sg.vEye = D3DXVECTOR4(_vEye.x, _vEye.y, _vEye.z, 0);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SIMPLECONSTANT_BUFFER0));
		m_pDeviceContext11->Unmap(m_pConstantBuffer0, 0);
	}



	//このコンスタントバッファーを使うシェーダーの登録
	m_pDeviceContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer0);
	m_pDeviceContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer0);
	//頂点インプットレイアウトをセット
	m_pDeviceContext11->IASetInputLayout(m_pVertexLayout);
	//プリミティブ・トポロジーをセット
	m_pDeviceContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//バーテックスバッファーをセット
	UINT stride = sizeof(MY_VERTEX);
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//属性の数だけ、それぞれの属性のインデックスバッファ－を描画
	for (DWORD i = 0; i<m_NumAttr; i++)
	{
		//使用されていないマテリアル対策
		if (m_pMaterial[m_AttrID[i]].dwNumFace == 0)
		{
			continue;
		}
		//インデックスバッファーをセット
		m_pDeviceContext11->IASetIndexBuffer(m_ppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);
		//マテリアルの各要素をエフェクト（シェーダー）に渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(m_pDeviceContext11->Map(m_pConstantBuffer1, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			SIMPLECONSTANT_BUFFER1 sg;
			sg.vAmbient = m_pMaterial[m_AttrID[i]].Ambient;//アンビエントををシェーダーに渡す
			sg.vDiffuse = m_pMaterial[m_AttrID[i]].Diffuse;//ディフューズカラーをシェーダーに渡す
			sg.vSpecular = m_pMaterial[m_AttrID[i]].Specular;//スペキュラーをシェーダーに渡す
			memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SIMPLECONSTANT_BUFFER1));
			m_pDeviceContext11->Unmap(m_pConstantBuffer1, 0);
		}
		m_pDeviceContext11->VSSetConstantBuffers(1, 1, &m_pConstantBuffer1);
		m_pDeviceContext11->PSSetConstantBuffers(1, 1, &m_pConstantBuffer1);
		//カラーテクスチャーをシェーダーに渡す
		if (m_pMaterial[m_AttrID[i]].pTexture)
		{
			m_pDeviceContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
			m_pDeviceContext11->PSSetShaderResources(0, 1, &m_pMaterial[m_AttrID[i]].pTexture);
		}
		//ノーマルマップ用テクスチャーをシェーダーに渡す
		m_pDeviceContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
		m_pDeviceContext11->PSSetShaderResources(1, 1, &m_pNormalTexture);

		//プリミティブをレンダリング
		m_pDeviceContext11->DrawIndexed(m_pMaterial[m_AttrID[i]].dwNumFace * 3, 0, 0);
	}

	D3DXMATRIX World, Tran, Rot;
	D3DXMatrixTranslation(&Tran, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixRotationY(&Rot, m_fYaw);


}



void CD3DXMESH::RenderRay(D3DXMATRIX& _mView, D3DXMATRIX& _mProj, D3DXVECTOR3& _vRayDir, float _RayLength)
{
	D3DXMATRIX mWorld, mScale, mRotation, mPosition;

	D3DXMatrixScaling(&mScale, _RayLength, _RayLength, _RayLength);
	D3DXMatrixRotationY(&mRotation, m_fYaw);
	D3DXMatrixTranslation(&mPosition, m_Pos.x, m_Pos.y, m_Pos.z);
	mWorld = mScale*mRotation*mPosition;

	//使用するシェーダーのセット
	m_pDeviceContext11->VSSetShader(m_pLineVertexShader, nullptr, 0);
	m_pDeviceContext11->PSSetShader(m_pLinePixelShader, nullptr, 0);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	LINE_CBUFFER cb;
	if (SUCCEEDED(m_pDeviceContext11->Map(m_pLineConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列を渡す
		cb.mWVP = mWorld*_mView*_mProj;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//カラーを渡す
		cb.Color = D3DXVECTOR4(1, 1, 0, 1);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext11->Unmap(m_pLineConstantBuffer, 0);
	}
	//このコンスタントバッファーを、どのシェーダーで使うかを指定
	m_pDeviceContext11->VSSetConstantBuffers(2, 1, &m_pLineConstantBuffer);//バーテックスバッファーで使う
	m_pDeviceContext11->PSSetConstantBuffers(2, 1, &m_pLineConstantBuffer);//ピクセルシェーダーで使う
																		   //バーテックスバッファーをセット
	UINT stride = sizeof(LINE_VERTEX);
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(0, 1, &m_pLineVertexBuffer, &stride, &offset);

	//頂点インプットレイアウトをセット
	m_pDeviceContext11->IASetInputLayout(m_pLineVertexLayout);
	//プリミティブ・トポロジーをセット
	m_pDeviceContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//プリミティブをレンダリング
	m_pDeviceContext11->Draw(2, 0);
}


bool CD3DXMESH ::VFCulling(CD3DXMESH* pMesh, D3DXMATRIX* pmView, float Angle, float NearClip, float FarClip, float Aspect)
{
	D3DXPLANE VFLeftPlane, VFRightPlane, VFTopPlane, VFBottomPlane;
	D3DXVECTOR3 Pos = pMesh->m_Pos;
	float Radius = pMesh->m_Radius;
	//まず、ジオメトリの位置ベクトルをワールドからビュー空間に変換
	D3DXVec3TransformCoord(&Pos, &Pos, pmView);

	//左右、上下の平面を計算
	{
		D3DXVECTOR3 p1, p2, p3;
		//左面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
		p2.y = -FarClip * (FLOAT)tan(Angle / 2);
		p2.z = FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
		//右面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
		p2.y = FarClip * (FLOAT)tan(Angle / 2);
		p2.z = FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
		//上面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
		p2.y = FarClip * (FLOAT)tan(Angle / 2);
		p2.z = FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
		//下面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = FarClip * ((FLOAT)tan(Angle / 2)*Aspect);
		p2.y = -FarClip * (FLOAT)tan(Angle / 2);
		p2.z = FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
	}

	//6つの平面とジオメトリ境界球をチェック
	{
		//ニアクリップ面について
		if ((Pos.z + Radius) < NearClip)
		{
			return false;
		}
		//ファークリップ面について
		if ((Pos.z - Radius) > FarClip)
		{
			return false;
		}
		//左クリップ面について
		float Distance = (Pos.x * VFLeftPlane.a) + (Pos.z * VFLeftPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//右クリップ面について
		Distance = (Pos.x * VFRightPlane.a) + (Pos.z * VFRightPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//上クリップ面について
		Distance = (Pos.y * VFTopPlane.b) + (Pos.z * VFTopPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//下クリップ面について
		Distance = (Pos.y * VFBottomPlane.b) + (Pos.z * VFBottomPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
	}

	return true;
}

HRESULT CD3DXMESH::LoadNomalMap(LPSTR _pTexFileName, ID3D11ShaderResourceView* _NomalMap)
{
	//ノーマルマップ用テクスチャーを読み込む
	if (FAILED(D3DX11CreateShaderResourceViewFromFileA(m_pDevice11,
		_pTexFileName, nullptr, nullptr, &m_pNormalTexture, nullptr)))
	{
		return E_FAIL;
	}
}

void CD3DXMESH::SetNomalMap(ID3D11ShaderResourceView* _nomalMap)
{

}
