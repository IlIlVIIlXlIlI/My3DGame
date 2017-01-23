#pragma once

#include "BASE.h"
#include "WINDOW.h"
#include "DIRECT3D11.h"
#include "CAMERA.h"
#include "CD3DXMESH.h"
#include "CD3DXMESH_ANIM.h"
#include "SOUND.h"
#include "D3D11_SPRITE.h"
#include "Player.h"
#include "Enemy.h"
#include "D3D11_TEXT.h"
#include "Collision.h"
#include "Frustum.h"
#include "UpdateLabel.h"
#include "BlackBar.h"


#define DEVICE		m_pD3d->m_pDevice
#define DCONTEXT	m_pD3d->m_pDeviceContext 

using namespace std;

class DIRECTOR : public CELEMENT
{
private:
	
	enum SCENE
	{
		/*
		ゲームのシーン
		*/
		INIT_OPENING,	//0 : 初期化(オープニング)

		OPENING,		//1 : オープニング

		INIT_STAGE1,	//2 : 初期化(ステージ1)

		PLAY_STAGE1,	//3 : ステージ1

		PLAY_STAGE2,	//4 : ステージ2

		WIN,			//5 : 勝利

		GAMEOVER,		//6 : ゲーム終了
	};


	//ResorceはShared_ptr
	//その他のポインタはunique_ptr

	//Data
	HINSTANCE					m_hInstance;
	HWND						m_hWnd;
	SCENE						m_Scene;
	unique_ptr<WINDOW>			m_pWindow;
	unique_ptr<DIRECT3D11>		m_pD3d;
	unique_ptr<CAMERA>			m_pCamera;
	shared_ptr<SOUND>			m_pSound;
	//=============================================================
	//スタティックメッシュ	
	//=============================================================
	shared_ptr<CD3DXMESH>		m_pMap_Start;			//フィールド
	shared_ptr<CD3DXMESH>		m_pMap_Start_Col;		//フィールド1のコリジョンモデル
	shared_ptr<CD3DXMESH>		m_pSkyBox;				//空
	shared_ptr<CD3DXMESH>		m_pMoveRock;			//岩
	shared_ptr<CD3DXMESH>		m_pOpenRock;			//開く岩
	shared_ptr<CD3DXMESH>		m_pPillar;
	
	//=============================================================
	//DEBUG STRING
	//=============================================================
#ifdef _DEBUG
	unique_ptr<D3D11_TEXT>		m_pText;
#endif
	//=============================================================
	//スプライトの作成
	//=============================================================

	/*タイトルで使う*/
	unique_ptr<SPRITE>			m_pTitle;
	unique_ptr<SPRITE>			m_pPressEnter;
	unique_ptr<SPRITE>			m_pExit;
	unique_ptr<SPRITE>			m_pTitlePlayer;
	unique_ptr<SPRITE>			m_pFadeIn;

	/*本編で使う*/
	unique_ptr<SPRITE>			m_pBlackBar;
	unique_ptr<SPRITE>			m_pUpdateLabel;
	unique_ptr<SPRITE>			m_pEscapeRoot;
	unique_ptr<SPRITE>			m_pElseRoot;
	//=============================================================
	//Xスキンメッシュアニメーションの作成
	//=============================================================
	shared_ptr<Player>			m_pPlayer;
	CD3DXMESH*					m_pPlayerSphere;

	//=============================================================
	//当たり判定
	//=============================================================
	unique_ptr<COLLISION>		m_pCollision;
	


	//=============================================================
	//スフィアの当たり判定
	//=============================================================
	//CD3DXMESH*					m_pSphereMesh;				//本物のスフィア
	shared_ptr<CD3DXMESH>			m_pSphereMesh;


	CD3DXMESH*					m_pMoveRock_Sphere1;		//岩のスフィア
	CD3DXMESH*					m_pCliff_Sphere2;			//崖を上るのスフィア
	CD3DXMESH*					m_pCliff_Sphere3;			//崖を渡るのスフィア
	shared_ptr<CD3DXMESH>		m_pCave_Sphere4;			//洞窟のスフィア
	shared_ptr<CD3DXMESH>		m_pDropAndOpenRock5;		//落ちてくる岩と開く岩スフィア
	shared_ptr<CD3DXMESH>		m_pClimeEndSphere6;			//崖を登り終える
	shared_ptr<CD3DXMESH>		m_pShimmyShpere7;
	//=============================================================
	//球との当たり判定
	//=============================================================
	HRESULT InitSphere(CD3DXMESH*);
	bool Collision(CD3DXMESH*, CD3DXMESH*);



	//=============================================================
	//視錘台カリング(View Frustum)
	//=============================================================
	shared_ptr<Frustum>			m_pViewFrustum;

	//=============================================================
	//Eキー(プッシュ)
	//=============================================================
	shared_ptr<SPRITE>			m_keyE;
	shared_ptr<SPRITE>			m_keyE2;
	shared_ptr<SPRITE>			m_keyC;

	//=============================================================
	//Updateのラベル
	//=============================================================
	unique_ptr<LABELCAL>		m_LabelCal;


	//=============================================================
	//BrackBarのラベル
	//=============================================================
	unique_ptr<BLACKBAR>		m_BB;

public:
	//Method
	DIRECTOR();
	~DIRECTOR();
	HRESULT		Init();
	void		Run(HINSTANCE);
	void		MainLoop();			//一番大事なループ
	void		FixFPS60();			//60FPS
	HRESULT		InitOpening();		//初期化(オープニング)
	void		Opening();			//オープニング
	HRESULT		InitStage1();		//初期化(ステージ1)
	void		Stage1();			//ステージ1

	float count;
	

	void objToSphere(CD3DXMESH*,CD3DXMESH*);



};

