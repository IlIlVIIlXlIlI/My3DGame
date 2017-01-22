#include "DIRECTOR.h"
#include <iostream>
using namespace std;
/*
MEMO

TODO : 後で手を付ける

FIX	 : 既知の不具合のあるコード

HACK : あまりきれいじゃない解決策

XXX  : 危険! 大きな問題がある

*/


void DIRECTOR::Stage1()
{
	//マルチスレッド
	//GET_THREAD.Update();

	
	///TODO : 当たり判定を簡略化する

	/*地形との距離を測る*/
	m_pPlayer->m_Distance = m_pCollision->RayGetDistance(m_hWnd,m_pPlayer.get(), m_pMap_Start_Col.get());
	//m_pPlayer->m_Distance = m_pCollision->RayGetDistance(m_hWnd, m_pPlayer.get(), m_pMoveRock.get());

	/*地面との当たり判定*/
	m_pCollision->RayIntersectDown(m_pPlayer.get(),m_pMap_Start.get(),&m_pPlayer->m_groundDis);

	
	//==============================================================================================
	//Camera 
	//==============================================================================================
	
	/*壁が近づくとプレイヤーに接近するカメラ*/
	//D3DXVECTOR3 Start = D3DXVECTOR3(0, 1.5, 0);//
	//D3DXVECTOR3 End = D3DXVECTOR3(0, 1.7, -4);
	//D3DXVec3TransformCoord(&Start, &Start, &m_pPlayer->mTrans);
	//D3DXVec3TransformCoord(&End, &End, &m_pPlayer->mTrans);
	//D3DXVECTOR3 EyePt = m_pCamera->GetRayDistance(m_pMap_Start_Col.get(),Start, End); //カメラ（視点）位置
	//D3DXVECTOR3 LookatPt = Start;//注視位置
	//D3DXVECTOR3 UpVec(0.0f, 1.0f, 0.0f);//上方位置


	//D3DXMatrixLookAtLH(&mView, &EyePt, &LookatPt, &UpVec);


	///TODO : カメラを簡略化する
	D3DXMATRIX mView, mProj;

	D3DXVec3TransformCoord(&m_pCamera->mCPos, &m_pCamera->mCPos, &m_pPlayer->m_CamRad);

	if (m_pPlayer->squatStatusFlg == TRUE)
	{
		m_pCamera->m_CamStatus = CAMERA::PLAYER_SQUAD;
	}
	
	if (m_pPlayer->bowStatusFlg == TRUE)
	{
		m_pCamera->m_CamStatus = CAMERA::PLAYER_BOW;
	}

	if (m_pPlayer->m_PlayerStatus == Player::GETTING_UP_STATUS)
	{
		m_pCamera->m_CamStatus = CAMERA::GETTING_UP;
	}

	m_pCamera->mCPos.x += m_pPlayer->mTrans._41;
	m_pCamera->mCPos.y += m_pPlayer->mTrans._42;
	m_pCamera->mCPos.z += m_pPlayer->mTrans._43;


	/*注視点設定*/
	m_pCamera->CLook = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformCoord(&m_pCamera->CLook, &m_pCamera->CLook, &m_pPlayer->mTrans);

	/*頭上方向設定*/
	D3DXVECTOR3 CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	/*視点行列の設定*/
	D3DXMatrixLookAtLH(&mView, &m_pCamera->mCPos, &m_pCamera->CLook, &CHead);

	/*プロジェクショントランスフォーム（射影変換）*/
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);


	

	//==============================================================================================
	//更新
	//==============================================================================================

	/*プレイヤー*/
	m_pPlayer->Player::Update();

	
	/*カメラ*/
	m_pCamera->Update();


	//==============================================================================================
	//Render
	//==============================================================================================
	static bool openRockFlg = TRUE;
	/*空*/
	m_pSkyBox->m_fYaw += 0.0001;
	m_pSkyBox->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	/*マップ*/
	m_pMap_Start->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
	//m_pMap_Start_Col->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	/*プレイヤー(本体)*/
	m_pPlayer->CD3DXSKINMESH::Render(mView, mProj, D3DXVECTOR3(0, -1, 0), m_pCamera->CLook);
	

	/*動かせる岩(本体)*/
	m_pMoveRock->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);


	/*開く岩*/
	if (openRockFlg == TRUE)
	{
		m_pOpenRock->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
	}
	

	//m_pCave_Sphere4->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	//==============================================================================================
	//Render(Sphere)
	//==============================================================================================

	/*ニセモノのスフィア(プレイヤーと同座標の球)*/
	m_pPlayerSphere->m_Pos = m_pPlayer->m_Pos;
	m_pPlayerSphere->m_Pos.y = m_pPlayer->m_Pos.y + 0.5;
	///m_pPlayerSphere->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	/*プレイヤーのスフィアを可視化*/
	if (GetAsyncKeyState('1') && 0x8000)
	{
		m_pSphereMesh->m_Pos = m_pPlayerSphere->m_Pos;		//プレイヤーの座標を本物のスフィアに入れる
		m_pSphereMesh->m_fScale = m_pPlayerSphere->m_Sphere.Radius * 2;
		m_pSphereMesh->Render(mView, mProj, D3DXVECTOR3(0, 1, -1), m_pCamera->CLook);

#ifdef _DEBUG
		std::cout << "プレイヤーの本物のスフィアを描画" << std::endl;
#endif
	}
	
	static bool sphereVisibility = FALSE;
	/*動かせる岩のEキースフィア1*/
	objToSphere(m_pMoveRock_Sphere1,m_pSphereMesh.get());
		
	/*動かせる岩のEキースフィア2*/
	objToSphere(m_pCliff_Sphere2, m_pSphereMesh.get());

	/*崖を渡るスフィア3*/
	objToSphere(m_pCliff_Sphere3, m_pSphereMesh.get());
	
	/*岩をくぐるスフィア4*/
	objToSphere(m_pCave_Sphere4.get(), m_pSphereMesh.get());

	/*落ちてくる岩と開くスフィア5*/
	objToSphere(m_pDropAndOpenRock5.get(), m_pSphereMesh.get());

	/*登り終えたときのスフィア6*/
	objToSphere(m_pClimeEndSphere6.get(), m_pSphereMesh.get());

	/*ぶら下がる箇所のスフィア7*/
	objToSphere(m_pShimmyShpere7.get(), m_pSphereMesh.get());


	/*2キーでスフィア可視化*/
	if (GetAsyncKeyState('2') && 0x8000)
	{
		if (sphereVisibility == FALSE)
		{
			///*岩を動かすためのスフィアを可視化*/
			m_pMoveRock_Sphere1->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*崖を登るためのスフィアを可視化*/
			m_pCliff_Sphere2->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*崖を渡るためのスフィアを可視化*/
			m_pCliff_Sphere3->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*岩をくぐるためのスフィアを可視化*/
			m_pCave_Sphere4->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*落ちてくる岩と開くスフィアを可視化*/
			m_pDropAndOpenRock5->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*登り終えるスフィアを可視化*/
			m_pClimeEndSphere6->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*ぶら下がるスフィアを可視化*/
			m_pShimmyShpere7->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
		}
	}
	else
	{
		sphereVisibility = FALSE;
	}


	//==============================================================================================
	//スフィアとの衝突判定
	//==============================================================================================
	static BOOL KeyFlg = FALSE;
	//スフィアに当たっているか
	static bool moveRockStartFlg = FALSE;
	/*プライヤーのスフィアと岩のあたり判定*/
	if (Collision(m_pPlayerSphere, m_pMoveRock_Sphere1))
	{

		SetWindowTextA(m_hWnd, "衝突しています");

		//キーの連打が8.0f以下
		if (m_pPlayer->KeyPanch <= 8.0f)
		{
			/*Eキースプライト*/
			m_keyE->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);


			m_pPlayer->m_PushRockFlg = TRUE;

			/*黒帯スプライト*/
			m_BB->Sum();
			m_pBlackBar->Render(D3DXVECTOR3(0, m_BB->posCount - 90, 0),1);
			m_pBlackBar->Render(D3DXVECTOR3(0, WINDOW_HEIGHT - m_BB->posCount, 0),1);



			if (GetAsyncKeyState('E') && 0x8000)
			{
				if (KeyFlg == FALSE)
				{
					KeyFlg = TRUE;
					m_pPlayer->KeyPanch += 0.1;
				}
			}
			else
			{
				KeyFlg = FALSE;
			}

			m_pPlayer->KeyPanch -= 0.001;

			if (m_pPlayer->KeyPanch >= 5.0)
			{
				m_pPlayer->m_PushinFlg = TRUE;
			}
			else
			{
				m_pPlayer->m_PushinFlg = FALSE;
			}
		}
		
		if (m_pPlayer->KeyPanch >= 8.0f)
		{
			m_pPlayer->m_PushRockFlg = FALSE;	//今押していない
			m_pPlayer->m_PushinFlg = FALSE;		//今押し込んでいない
			m_pPlayer->m_PushNow = FALSE;		//今押していない

			moveRockStartFlg = TRUE;
		}

		
		
	}
	
	if (moveRockStartFlg == TRUE)
	{	
		if(m_pMoveRock->m_Pos.y >= -3.2)m_pMoveRock->m_fPitch += 0.01;

		m_pMoveRock->m_Pos.z += 0.01;

		if (m_pMoveRock->m_Pos.z >= 28.0)
		{
			m_pMoveRock->m_Pos.y -= 0.01;
		}

		if (m_pMoveRock->m_Pos.z >= 32.5)
		{
			m_pMoveRock->m_Pos.z = 32.5;
			
		}

		if (m_pMoveRock->m_Pos.y <= -3.2)
		{
			m_pMoveRock->m_Pos.y = -3.2;
			moveRockStartFlg = FALSE;
		}
			
	}


	/*クライミング*/
	if (Collision(m_pPlayerSphere, m_pCliff_Sphere2))
	{
		SetWindowTextA(m_hWnd, "衝突しています");
		m_pPlayer->m_ClimingFlg = TRUE;
		/*Cキースプライト*/
		m_keyC->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);
	}
	
	/*壁歩き*/
	if (Collision(m_pPlayerSphere, m_pCliff_Sphere3))
	{
		SetWindowTextA(m_hWnd, "衝突しています");
		m_pPlayer->m_CoverFlg = TRUE;
		/*Eキースプライト*/
		m_keyE->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);
	}


	/*岩くぐり*/
	if (Collision(m_pPlayerSphere, m_pCave_Sphere4.get()))
	{
		SetWindowTextA(m_hWnd, "衝突しています");

		if (GetAsyncKeyState('E') && 0x8000)
		{
			m_pPlayer->squatStatusFlg = TRUE;
		}

		/*Eキースプライト*/
		m_keyE->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);
	}

	static bool moveRockFlg = 0;
	static float moveRockDrop = 40.0;
	/*落ちてくる岩と開く*/
	if (Collision(m_pPlayerSphere, m_pDropAndOpenRock5.get()))
	{
		SetWindowTextA(m_hWnd, "衝突しています");	
		moveRockFlg = 1;
		openRockFlg = FALSE;

	}
	if (moveRockFlg == 1)
	{
		m_pMoveRock->m_Pos = D3DXVECTOR3(0.31f, moveRockDrop, 124.0f);
		m_pMoveRock->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
		moveRockDrop -= 0.2;
		if (moveRockDrop <= 18.6)moveRockDrop = 18.6;
	}

	/*崖を登り終える*/
	/*if (GetAsyncKeyState('L') && 0x8000)
	{
		m_pPlayer->m_ClimeEndFlg = TRUE;
	}*/
	/*if (Collision(m_pPlayerSphere,m_pClimeEndSphere6.get()))
	{
		SetWindowTextA(m_hWnd, "ここで登り終えるよ！");
		m_pPlayer->m_ClimeEndFlg = TRUE;
	}

	if (m_pPlayer->m_ClimeEndCount >= 30)
	{
		m_pPlayer->m_Pos = D3DXVECTOR3(1.0f, 14.6f, 36.2f);
	}*/


	/*ぶら下がるスフィアとの当たり判定*/
	if (Collision(m_pPlayerSphere, m_pShimmyShpere7.get()))
	{

	}
	//==============================================================================================
	//視錘台カリング
	//==============================================================================================
	//static bool frustumFlg = 0;
	//if (m_pViewFrustum->VFCulling
	//	(m_pPlayer.get(), &mView, D3DX_PI / 4, 1.0, 10000, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT))
	//{
	//	frustumFlg = 1;	
	//}
	//else
	//{
	//	frustumFlg = 0;
	//}




	//==============================================================================================
	//Sprite Draw
	//==============================================================================================

	/*Updateラベル*/
	
	

	/*アップデートラベルを描画*/
	m_pUpdateLabel->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) + m_LabelCal->markCount, WINDOW_HEIGHT / 2, 0), 0.5);
	
	/*アップデートラベルの出現を計算*/
	m_LabelCal->UpdateLabel();

	
	/*ラベルの表示の仕方を計算*/
	m_LabelCal->MissionLabel();
	



	if (openRockFlg == FALSE)
	{
		/*別ルートを探す*/
		m_pElseRoot->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) + m_LabelCal->labelCount, (WINDOW_HEIGHT / 2) + 30, 0), 0.5);
	}
	else
	{
		/*脱出ルートを探す*/
		m_pEscapeRoot->Render(D3DXVECTOR3((WINDOW_WIDTH / 2)+ m_LabelCal->labelCount , (WINDOW_HEIGHT / 2) + 30, 0), 0.5);
	}

	if (GetAsyncKeyState('P') && 0x8000)
	{
		m_Scene = PLAY_STAGE1;
	}
	


	//==============================================================================================
	//Sound 
	//==============================================================================================
	//m_pSound->PlaySound(0,false);

	//==============================================================================================
	//DEBUG STRING
	//==============================================================================================
#ifdef _DEBUG
	char sz[512] = { 0 };
	sprintf_s(sz, "X = %0.3f", m_pPlayer->m_Pos.x);
	m_pText->Render(sz, 0, 70);

	char sz2[512] = { 0 };
	sprintf_s(sz2, "Y = %0.3f", m_pPlayer->m_Pos.y);
	m_pText->Render(sz2, 0, 100);

	char sz3[512] = { 0 };
	sprintf_s(sz3, "Z = %0.3f", m_pPlayer->m_Pos.z);
	m_pText->Render(sz3, 0, 130);

	char sz4[512] = { 0 };
	sprintf_s(sz4, "KeyPanch = %0.2f", m_pPlayer->KeyPanch);
	m_pText->Render(sz4, 0, 160);

	char sz5[512] = { 0 };
	sprintf_s(sz4, "moveRockStartFlg %d", moveRockStartFlg);
	m_pText->Render(sz4, 0, 190);

	//==================
	//デバッグキー
	//==================
	//壁横歩きの場所までワープ
	if (GetAsyncKeyState('H') && 0x8000)
	{
		m_pPlayer->m_Pos = D3DXVECTOR3(-77.9, 6.8, 122.5);
	}
	//==================
	//レイの描画
	//==================
	m_pPlayer->RenderRay(mView, mProj, D3DXVECTOR3(0, 0, 1), RAY_DISTANCE);


#endif

	
}

/*オブジェクトの位置にスフィアの位置を入れる*/
void DIRECTOR::objToSphere(CD3DXMESH* _pObj, CD3DXMESH* _Sphere)
{
	_Sphere->m_Pos = _pObj->m_Pos;
	_Sphere->m_Pos.y = _pObj->m_Pos.y + 0.5;
	_Sphere->m_fScale = _pObj->m_Sphere.Radius * 2;
}


