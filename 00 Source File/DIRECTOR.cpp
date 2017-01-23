#include "DIRECTOR.h"


 
//
DIRECTOR::DIRECTOR()
{
	/*
	初期シーンをステージ1に
	*/
	ZeroMemory(this,sizeof(DIRECTOR));
	m_Scene = INIT_OPENING;
	count = 0.0f;
}
//
//
///HACK : スマートポインタに置き換えたため今は必要ない
DIRECTOR::~DIRECTOR()
{
	////SAFE_DELETE(m_pSound);
	//SAFE_DELETE(m_pPlayer);
}


void DIRECTOR::Run(HINSTANCE hInstance)
{
	char dir[512];
	GetCurrentDirectory(sizeof(dir),dir);
	InitDirectory(dir);

	m_hInstance=hInstance;
	if(FAILED(Init()))
	{
		return;
	}
	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd) ;
	// メッセージループ
	MSG msg={0};
	ZeroMemory(&msg,sizeof(msg));


	while(msg.message!=WM_QUIT)
	{
		if( PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainLoop();
		}
	}
}
//
//
//
void DIRECTOR::MainLoop()
{
	m_pD3d->Clear();
	switch (m_Scene)
	{
	case INIT_OPENING:
		InitOpening();
		break;

	case OPENING:
		Opening();
		break;

	case INIT_STAGE1:
		InitStage1();
		break;

	case PLAY_STAGE1:
		Stage1();
		break;

	case WIN:
		break;

	case GAMEOVER:
		break;

	default:
		assert(!"XXX:不正なゲームステータスです");

	}
	

	FixFPS60();
	m_pD3d->Present();
}
//
//
//
HRESULT DIRECTOR::Init()
{
	/*Windowの作成*/
	m_pWindow= make_unique<WINDOW>();

	if(!m_pWindow)
	{
		return E_FAIL;
	}
	MFAIL(m_pWindow->InitWindow(m_hInstance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME), "ウィンドウ");
	m_hWnd=m_pWindow->m_hWnd;
	
	/*DircetX11*/
	D3D_INIT di;
	m_pD3d= make_unique<DIRECT3D11>();

	
	/*DirectX11の初期化失敗かどうか*/
	if(m_pD3d==nullptr)
	{
		MSG("Direct3Dの初期化失敗");
		return E_FAIL;
	}

	di.hWnd = m_hWnd;
	MFAIL(m_pD3d->Init(&di),"Direct3D初期化失敗");


	return S_OK;
}
//
//
//
void DIRECTOR::FixFPS60()
{
	static INT Frames=0,FPS=0;
	static LARGE_INTEGER Frq={0},PreviousTime={0},CurrentTime={0};
	DOUBLE Time=0;
	char sz[11]={0};

	while(Time<16.6666)//1100ms / 60frame=16.6666 
	{
		assert((Time <= 16.6666), "XXX:不正な数値です");
		QueryPerformanceFrequency(&Frq);
		
		QueryPerformanceCounter(&CurrentTime);
		Time=CurrentTime.QuadPart-PreviousTime.QuadPart;
		Time *=(DOUBLE)1100.0 / (DOUBLE)Frq.QuadPart;		
	}
	PreviousTime=CurrentTime;
}


HRESULT DIRECTOR::InitSphere(CD3DXMESH* pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	void* pVertices = NULL;
	D3DXVECTOR3 vCenter;
	float fRadius;

	//メッシュの頂点バッファーをロックする
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}
	// メッシュの外接円の中心と半径を計算する
	D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices, pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()), &vCenter, &fRadius);

	pVB->Unlock();
	SAFE_RELEASE(pVB);

	

//	pMesh->m_Sphere->Center = vCenter;
	pMesh->m_Sphere.Radius = fRadius*0.7;//そのままでは、あまりにも無駄すぎるので縮小

										 //これ以降の行は本来は不要。確認のためスフィア自体をレンダリングするためのもの

										 // 得られた中心と半径を基に可視化用メッシュとしてのスフィアを作成する
	SetVisualDirectory();
	//m_pSphereMesh = shared_ptr<CD3DXMESH>();
	/*m_pSphereMesh = new CD3DXMESH;
	m_pSphereMesh->Init(m_hWnd, DEVICE, DCONTEXT, "Sphere.x");*/

	m_pSphereMesh = make_shared<CD3DXMESH>
		(m_hWnd,DEVICE,DCONTEXT,(LPSTR)"Sphere.x");

	return S_OK;
}

//
//
bool DIRECTOR::Collision(CD3DXMESH* pMeshA, CD3DXMESH* pMeshB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pMeshB->m_Pos - pMeshA->m_Pos;
	float Length = D3DXVec3Length(&vLength);
	//2物体間の距離が、2物体の半径を足したものより小さいということは、
	//境界球同士が重なっている（衝突している）ということ
	if (Length <= pMeshA->m_Sphere.Radius + pMeshB->m_Sphere.Radius)
	{
		return true;
	}
	return false;
}
