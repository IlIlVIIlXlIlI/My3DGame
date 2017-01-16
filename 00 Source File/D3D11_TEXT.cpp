#include "D3D11_TEXT.h"

//
//
//
D3D11_TEXT::D3D11_TEXT()
{
	ZeroMemory(this,sizeof(D3D11_TEXT));
	m_fScale=1.0f;
	//カーニング量を個別に設定

	m_fKerning[0]=23;//space
	m_fKerning[1]=16;//!
	m_fKerning[2]=19;//"
	m_fKerning[3]=22;//#
	m_fKerning[4]=22;//$
	m_fKerning[5]=23;//%
	m_fKerning[6]=23;//&
	m_fKerning[7]=18;//'
	m_fKerning[8]=16;//(
	m_fKerning[9]=16;//)
	m_fKerning[10]=18;//*
	m_fKerning[11]=20;//+
	m_fKerning[12]=17;//,
	m_fKerning[13]=17;//-
	m_fKerning[14]=18;//.
	m_fKerning[15]=19;// /
	m_fKerning[16]=20;//0
	m_fKerning[17]=17;//1
	m_fKerning[18]=20;//2
	m_fKerning[19]=21;//3
	m_fKerning[20]=20;//4
	m_fKerning[21]=20;//5
	m_fKerning[22]=20;//6
	m_fKerning[23]=20;//7
	m_fKerning[24]=20;//8
	m_fKerning[25]=20;//9
	m_fKerning[26]=16;//:
	m_fKerning[27]=16;//;
	m_fKerning[28]=18;//<
	m_fKerning[29]=20;//=
	m_fKerning[30]=21;//>
	m_fKerning[31]=19;//?
	m_fKerning[32]=22;//@
	m_fKerning[33]=21;//A
	m_fKerning[34]=20;//B
	m_fKerning[35]=20;//C
	m_fKerning[36]=22;//D
	m_fKerning[37]=20;//E
	m_fKerning[38]=21;//F
	m_fKerning[39]=22;//G
	m_fKerning[40]=22;//H
	m_fKerning[41]=19;//I
	m_fKerning[42]=19;//J
	m_fKerning[43]=19;//K
	m_fKerning[44]=23;//L
	m_fKerning[45]=24;//M
	m_fKerning[46]=21;//N
	m_fKerning[47]=23;//O
	m_fKerning[48]=20;//P
	m_fKerning[49]=22;//Q
	m_fKerning[50]=20;//R
	m_fKerning[51]=22;//S
	m_fKerning[52]=21;//T
	m_fKerning[53]=21;//U
	m_fKerning[54]=24;//V
	m_fKerning[55]=25;//W
	m_fKerning[56]=20;//X
	m_fKerning[57]=20;//Y
	m_fKerning[58]=20;//Z
	m_fKerning[59]=15;//[
	m_fKerning[60]=17;// \/
	m_fKerning[61]=15;//]
	m_fKerning[62]=19;//^
	m_fKerning[63]=21;//_
	m_fKerning[64]=17;//`
	m_fKerning[65]=21;//a
	m_fKerning[66]=21;//b
	m_fKerning[67]=18;//c
	m_fKerning[68]=20;//d
	m_fKerning[69]=19;//e
	m_fKerning[70]=18;//f
	m_fKerning[71]=20;//g
	m_fKerning[72]=18;//h
	m_fKerning[73]=14;//i
	m_fKerning[74]=19;//j
	m_fKerning[75]=21;//k
	m_fKerning[76]=22;//l
	m_fKerning[77]=24;//m
	m_fKerning[78]=20;//n
	m_fKerning[79]=19;//o
	m_fKerning[80]=20;//p
	m_fKerning[81]=19;//q
	m_fKerning[82]=17;//r
	m_fKerning[83]=17;//s
	m_fKerning[84]=19;//t
	m_fKerning[85]=20;//u
	m_fKerning[86]=22;//v
	m_fKerning[87]=22;//w
	m_fKerning[88]=19;//x
	m_fKerning[89]=19;//y
	m_fKerning[90]=19;//z
	m_fKerning[91]=16;//{
	m_fKerning[92]=14;//|
	m_fKerning[93]=18;//}
	m_fKerning[94]=19;//~
	
}


//
//
//
HRESULT D3D11_TEXT::Init(ID3D11DeviceContext* pContext,DWORD width,DWORD height,float size,D3DXVECTOR4 vColor)
{
	m_fAlpha=vColor.w;
	m_vColor=vColor;
	m_fScale=size/25.0f;

	for(int i=0;i<95;i++)
	{
		m_fKerning[i]*=m_fScale;
	}
	//デバイスとコンテキストをコピー
	m_pDeviceContext=pContext;
	m_pDeviceContext->GetDevice(&m_pDevice);
	//window サイズ
	m_dwWindowWidth=width;
	m_dwWindowHeight=height;
	//フォントごとにクアッド作成
	float left=0,top=0,right=0,bottom=0;
	float dimension=DIMENSION/2.0f;
	int cnt=0;
	for(int k=0;k<10;k++)
	{
		for(int i=0;i<10;i++)
		{
			left=k*DIMENSION;
			top=i*DIMENSION+6;
			right=left+(m_fKerning[cnt]+1);
			bottom=top+(DIMENSION*m_fScale-1);
			left/=TEX_DIMENSION;
			top/=TEX_DIMENSION;
			right/=TEX_DIMENSION;
			bottom/=TEX_DIMENSION;
			SimpleVertex_TEXT vertices[]=
			{
				D3DXVECTOR3( 0,DIMENSION*m_fScale,0),D3DXVECTOR2(left,bottom),//頂点1,
				D3DXVECTOR3(0,0,0), D3DXVECTOR2(left,top),//頂点2
				D3DXVECTOR3( DIMENSION*m_fScale,DIMENSION*m_fScale,0),D3DXVECTOR2(right,bottom), //頂点3
				D3DXVECTOR3(  DIMENSION*m_fScale,0,0),D3DXVECTOR2(right,top), //頂点4
			};
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(SimpleVertex_TEXT)*4;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;
			if( FAILED( m_pDevice->CreateBuffer( &bd, &InitData, &m_pVertexBuffer[cnt] ) ) )
			{
				return E_FAIL;
			}
			cnt++;
		}
	}
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc,sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState( &SamDesc, &m_pSampleLinear);
	//フォントのテクスチャーを作成
	if(FAILED(D3DX11CreateShaderResourceViewFromFile(m_pDevice, "01 Data File//ascii.png", nullptr, nullptr, &m_pAsciiTexture, nullptr )))
	{
		return E_FAIL;
	}
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob *pCompiledShader=nullptr;
	ID3DBlob *pErrors=nullptr;
	//ブロブからバーテックスシェーダー作成
	if(FAILED(D3DX11CompileFromFile("03 Shader File//D3D11_TEXT.hlsl",nullptr,nullptr,"VS","vs_5_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
	{
		MessageBox(0,"hlsl読み込み失敗",nullptr,MB_OK);
		return E_FAIL;
    }
	SAFE_RELEASE(pErrors);

	if(FAILED(m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),nullptr,&m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0,"バーテックスシェーダー作成失敗(D3D11_TEXT)",nullptr,MB_OK);
		return E_FAIL;
	}
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
	};
	UINT numElements = sizeof(layout)/sizeof(layout[0]);

	//頂点インプットレイアウトを作成
	if( FAILED( m_pDevice->CreateInputLayout( layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout ) ) )
		return FALSE;
	//ブロブからピクセルシェーダー作成
	if(FAILED(D3DX11CompileFromFile("03 Shader File//D3D11_TEXT.hlsl",nullptr,nullptr,"PS","ps_5_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
	{
		MessageBox(0,"hlsl読み込み失敗",nullptr,MB_OK);
		return E_FAIL;
    }
	SAFE_RELEASE(pErrors);
	if(FAILED(m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),nullptr,&m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0,"ピクセルシェーダー作成失敗",nullptr,MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//コンスタントバッファー作成　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= sizeof( CONSTANT_BUFFER_TEXT);
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	=0;
	cb.StructureByteStride=0;
	cb.Usage=D3D11_USAGE_DYNAMIC;

	if( FAILED(m_pDevice->CreateBuffer( &cb,nullptr,&m_pConstantBuffer)))
	{
		return E_FAIL;
	}
	//抜け色設定
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable =false;
	bd.AlphaToCoverageEnable=false;
	bd.RenderTarget[0].BlendEnable=true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	if(FAILED(m_pDevice->CreateBlendState(&bd, &m_pBlendState)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//
//
//
void D3D11_TEXT::Render(char* text,int x,int y)
{
	// ビュートランスフォーム（視点座標変換）
	D3DXVECTOR3 vEyePt( 0.0f, 0.0f,-1 ); //カメラ（視点）位置
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );//注視位置
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );//上方位置
	D3DXMatrixLookAtLH( &m_mView, &vEyePt, &vLookatPt, &vUpVec );

	// プロジェクショントランスフォーム（射影変換）
	D3DMATRIX mOtho = {
		2.0f /(float) ( m_dwWindowWidth ), 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f /(float) ( m_dwWindowHeight ), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
		};
	m_mProj=mOtho;

	//トポロジー
	m_pDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	
	//頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout( m_pVertexLayout );

	//使用するシェーダーの登録
	m_pDeviceContext->VSSetShader(m_pVertexShader,nullptr,0);
	m_pDeviceContext->PSSetShader(m_pPixelShader,nullptr,0);
	//このコンスタントバッファーを使うシェーダーの登録
	m_pDeviceContext->VSSetConstantBuffers(0,1,&m_pConstantBuffer );
	m_pDeviceContext->PSSetConstantBuffers(0,1,&m_pConstantBuffer );
	//テクスチャーをシェーダーに渡す
	m_pDeviceContext->PSSetSamplers(0,1,&m_pSampleLinear);
	m_pDeviceContext->PSSetShaderResources(0,1,&m_pAsciiTexture);
	
	//render
	for(int i=0;i<strlen(text);i++)
	{
		char font=text[i];
		int index=font-32;
		RenderFont(index,x,y);
		x+=m_fKerning[index];
	}
}
//
//
//
void D3D11_TEXT::RenderFont(int FontIndex,int x,int y)
{
	//ワールド変換
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixTranslation(&mWorld,x,y,-100);
	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_TEXT cb;
	if( SUCCEEDED( m_pDeviceContext->Map( m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{
		//ワールド、カメラ、射影行列を渡す
		D3DXMATRIX m=mWorld*m_mView*m_mProj;
		D3DXMatrixTranspose( &m, &m );
		cb.mWVP=m;
		//カラーを渡す
		cb.vColor=m_vColor;
		//透明度を渡す
		cb.fAlpha.x=m_fAlpha;

		memcpy_s( pData.pData, pData.RowPitch, (void*)( &cb), sizeof( cb ) );
		m_pDeviceContext->Unmap( m_pConstantBuffer, 0 );
	}
	//バーテックスバッファーをセット
	UINT stride = sizeof( SimpleVertex_TEXT );
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer[FontIndex], &stride, &offset );

	//抜け色
	UINT ColorKey=0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, ColorKey);
	m_pDeviceContext->Draw( 4, 0 );
}