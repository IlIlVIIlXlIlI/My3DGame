#include "DIRECTOR.h"

/*
MEMO

TODO : 後で手を付ける

FIX	 : 既知の不具合のあるコード

HACK : あまりきれいじゃない解決策

XXX  : 危険! 大きな問題がある

*/

HRESULT DIRECTOR::InitStage1()
{
	//==========================================================================
	//DEBUG String
	//==========================================================================
#ifdef _DEBUG
	m_pText = make_unique<D3D11_TEXT>();

	D3DXVECTOR4 vColor(1.0, 1.0, 1.0, 1.0);
	if (FAILED(m_pText->Init
		(DCONTEXT, WINDOW_WIDTH, WINDOW_HEIGHT, 25, vColor)))
	{
		return E_FAIL;
	}

#endif

	//==========================================================================
	//スプライトの作成
	//==========================================================================
	m_pBlackBar = make_unique<SPRITE>
		(DCONTEXT, (LPSTR)"BlackBar.png", 1280, 90);
	
	m_pUpdateLabel = make_unique<SPRITE>
		(DCONTEXT, (LPSTR)"Update.png", 276, 57);

	m_pEscapeRoot = make_unique<SPRITE>
		(DCONTEXT, (LPSTR)"EscapeRoot.png", 276, 57);
	

	m_pElseRoot = make_unique<SPRITE>
		(DCONTEXT, (LPSTR)"ElseRoot.png", 276, 57);
	//==========================================================================
	//メッシュ読み込み
	//==========================================================================
	//マップ
	SetVisualDirectory();
	m_pMap_Start = make_shared<CD3DXMESH>();
		m_pMap_Start->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Start.x","Rock_SharpStainedCliff_2k_n.png");


	//マップのコリジョンモデル
	SetVisualDirectory();
	m_pMap_Start_Col = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Start_Col.x");

	//空のモデル
	SetVisualDirectory();
	m_pSkyBox = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sky.x");
	m_pSkyBox->m_fScale = 3.0f;

	//動かせる岩のモデル
	SetVisualDirectory();
	m_pMoveRock = make_shared<CD3DXMESH>();
		m_pMoveRock->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"moveRock.x","Rock_SharpStainedCliff_2k_n.png");
	m_pMoveRock->m_Pos = D3DXVECTOR3(1, 2, 25);


	//柱
	SetVisualDirectory();
	m_pPillar = make_shared<CD3DXMESH>();
	m_pPillar->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"pillar.x", "Misc_StonePillar_1k_n.png");
	m_pPillar->m_Pos = D3DXVECTOR3(0, 0, 0);



	//ツタ
	SetVisualDirectory();
	m_pIvy = make_shared<CD3DXMESH>();
	m_pIvy->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Ivy.x", "Misc_SmallLeafHedge_2k_n.png");
	m_pIvy->m_Pos = D3DXVECTOR3(0, 0, 0);
	

	//開く岩
	SetVisualDirectory();
	m_pOpenRock = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"OpenRock.x");
	//============================================================================
	//当たり判定用のスフィア
	//============================================================================

	//動かせる岩
	SetVisualDirectory();
	m_pMoveRock_Sphere1 = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pMoveRock_Sphere1->m_Pos = D3DXVECTOR3(1.0f, 0.0f, 21.0f);
	/*スフィアを作る(動かせる岩)*/
	InitSphere(m_pMoveRock_Sphere1);



	//上れる崖
	SetVisualDirectory();
	m_pCliff_Sphere2 = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pCliff_Sphere2->m_Pos = D3DXVECTOR3(1,0,35.0);
	/*スフィアを作る(上れる崖)*/
	InitSphere(m_pCliff_Sphere2);


	//渡れる崖
	SetVisualDirectory();
	m_pCliff_Sphere3 = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pCliff_Sphere3->m_Pos = D3DXVECTOR3(-77.7f, 7.0f, 122.9);
	/*スフィアを作る(渡れる崖)*/
	InitSphere(m_pCliff_Sphere3);


	//潜れる岩		
	SetVisualDirectory();
	m_pCave_Sphere4 = make_shared<CD3DXMESH>();
	m_pCave_Sphere4->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pCave_Sphere4->m_Pos = D3DXVECTOR3(-52.3f, 6.49f, 179.5f);


	//落ちてくる岩と開く岩
	SetVisualDirectory();
	m_pDropAndOpenRock5 = make_shared<CD3DXMESH>();
	m_pDropAndOpenRock5->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pDropAndOpenRock5->m_Pos = D3DXVECTOR3(0.3f, 15.3f, 103.097f);


	//クリアスフィア
	SetVisualDirectory();
	m_pClearSphere = make_shared<CD3DXMESH>();
	m_pClearSphere->Init(m_hWnd,DEVICE,DCONTEXT,(LPSTR)"Sphere.x");
	m_pClearSphere->m_Pos = D3DXVECTOR3(-23.0f, 18.6f, 201.8f);
	//m_pClearSphere->m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//崖を昇るスフィア
	SetVisualDirectory();
	m_pClimeSphere = make_shared<CD3DXMESH>();
	m_pClimeSphere->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pClimeSphere->m_Pos = D3DXVECTOR3(-23.9, 6.5, 198.3);

	//============================================================================
	//SKINMESH
	//============================================================================
	//プレイヤー
	SetVisualDirectory();
	m_pPlayer = make_shared<Player>();
	m_pPlayer->InitSM(m_hWnd, DEVICE, DCONTEXT);
	m_pPlayer->CreateFromX("player21.x");




	//ニセモノのスフィア
	SetVisualDirectory();
	m_pPlayerSphere = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pPlayerSphere->m_Pos = m_pPlayer->m_Pos;

	/*スフィアを作る(プレイヤー)*/
	InitSphere(m_pPlayerSphere);


	

	//============================================================================
	//キープッシュ
	//============================================================================
	/*Eキー*/
	SetRootDirectory();
	m_keyE = make_shared<SPRITE>
		(DCONTEXT, (LPSTR)"E_KEY.png", 94, 92);
	
	/*Eキー2*/
	SetRootDirectory();
	m_keyE2 = make_shared<SPRITE>
		(DCONTEXT, (LPSTR)"E_KEY2.png", 94, 92);

	/*Cキー*/
	SetRootDirectory();
	m_keyC = make_shared<SPRITE>
		(DCONTEXT, (LPSTR)"C_KEY.png", 94, 92);


	//============================================================================
	//ステージクリア
	//============================================================================
	SetRootDirectory();
	m_pStage1Clear = make_unique<SPRITE>
		(DCONTEXT, (LPSTR)"STAGE1CLEAR.png", 801, 141);


	SetRootDirectory();
	m_pBackGround = make_unique<SPRITE>
		(DCONTEXT, (LPSTR)"BackGround.png", 600, 400);

	//=============================================================
	//Updateラベル
	//=============================================================
	m_LabelCal = make_unique<LABELCAL>();


	//============================================================================
	//camera
	//============================================================================
	m_pCamera = make_unique<CAMERA>
		(WINDOW_WIDTH,WINDOW_HEIGHT);
	m_pCamera->SetCameraPosition(0, 0, -1);


	//============================================================================
	//Sound(XAuido2)
	//============================================================================
	//m_pSound = new SOUND;
	m_pSound = make_shared<SOUND>();
	MFAIL(m_pSound->Init(), "サウンド初期化失敗");

	//============================================================================
	//サウンド読み込み
	//============================================================================
	SetSoundDirectory();
	m_pSound->LoadSound("m1.wav");



	//============================================================================
	//シーンをステージ1に
	//============================================================================
	m_Scene = PLAY_STAGE1;


	//=============================================================
	//BrackBar
	//=============================================================
	m_BB = make_unique<BLACKBAR>();
	return S_OK;
}