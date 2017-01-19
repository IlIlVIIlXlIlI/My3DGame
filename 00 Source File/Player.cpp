#include "Player.h"


Player::Player()
{
	move = 0.06;						//移動量

	m_Dir = D3DXVECTOR3(0, 0, 1);		//方向
	
	m_Pos = D3DXVECTOR3(0, 0, 0);		//座標
			
	m_Scale = D3DXVECTOR3(1, 1, 1);		//拡大行列

	/*操作していない時は、常に通常状態に*/
	m_PlayerStatus = GETTING_UP_STATUS;

	tmpRot = 0.0f;

	KeyPanch = 0.0f;

	m_Distance = 999;

	m_AnimFarstCount = 0.0f;

	m_PushRockFlg = FALSE;

	m_PushinFlg = FALSE;

	m_PushNow = FALSE;

	m_ClimeEndFlg = FALSE;

	m_ClimeEndCount = 0.0f;
			
	m_OperationPossible = TRUE;
}


void Player::Update()
{
	//===============================================================
	//カメラの回転
	//===============================================================
	CameraRotate();
	

	//MEMO (リアルタイムで書き込み)
	//0 : しゃがむ
	//1 : 走る
	//2 : 通常(立ち)
	//3 : しゃがむ(前に動く)
	//4 : しゃがむ(右に動く)
	//5 : しゃがむ(後ろに動く)
	//6 : しゃがむ(左に動く)
	//7 : 弓を構える
	//8 : ランニング
	//9 : クライミング(UP)
	//10: ジャンプ
	//===============================================================
	//キャラクターの状態変化
	//===============================================================

	///TODO : Stateパターンに置き換える

	switch (m_PlayerStatus)
	{
	case SQUAT_STATUS:	
		ChangeAnim(0);		//しゃがむ
		m_pD3dxMesh->m_hlAnimationList[0]->Speed = 0.020;
		break;

	case JOGGING_STATUS:		//ジョギング
		ChangeAnim(1);
		m_pD3dxMesh->m_hlAnimationList[1]->Speed = 0.020;
		break;

	case SQUAT_FORWARD_STATUS:	//しゃがむ(前に動く)
		ChangeAnim(3);
		m_pD3dxMesh->m_hlAnimationList[3]->Speed = 0.020;
		break;

	case SQUAT_RIGHT_STATUS:	//しゃがむ(右に動く)
		ChangeAnim(4);
		m_pD3dxMesh->m_hlAnimationList[4]->Speed = 0.020;
		break;

	case SQUAT_BACK_STATUS:		//しゃがむ(後ろに動く)
		ChangeAnim(5);
		m_pD3dxMesh->m_hlAnimationList[5]->Speed = 0.020;
		break;

	case SQUAT_LEFT_STATUS:		//しゃがむ(左に動く)
		ChangeAnim(6);
		m_pD3dxMesh->m_hlAnimationList[6]->Speed = 0.020;
		break;

	case BOW_READY_STATUS:		//弓を構える
		ChangeAnim(7);
		m_pD3dxMesh->m_hlAnimationList[7]->Speed = 0.020;
		break;

	case RUNNING_STATUS:		//ランニング
		ChangeAnim(8);
		m_pD3dxMesh->m_hlAnimationList[8]->Speed = 0.015;
		break;

	case CLIMING_STATUS:		//クライミング(UP)
		ChangeAnim(9);
		m_pD3dxMesh->m_hlAnimationList[9]->Speed = 0.020;
		break;

	case JUMP_STATUS:			//ジャンプ
		ChangeAnim(10);
		m_pD3dxMesh->m_hlAnimationList[10]->Speed = 0.015;
		break;

	case COVER_LEFT_STATUS:		//左壁歩き
		ChangeAnim(11);
		m_pD3dxMesh->m_hlAnimationList[11]->Speed = 0.012;
		break;

	case COVER_RIGHT_STATUS:	//右壁歩き
		ChangeAnim(12);
		m_pD3dxMesh->m_hlAnimationList[12]->Speed = 0.012;
		break;

	case GETTING_UP_STATUS:		//立ち上がり(最初のモーション)
		ChangeAnim(13);
		m_pD3dxMesh->m_hlAnimationList[13]->Speed = 0.015;
		break;

	case PUSH_ROCK_STATUS:		//岩を押す
		ChangeAnim(14);
		m_pD3dxMesh->m_hlAnimationList[14]->Speed = 0.015;
		break;

	case PUSHING_ROCK_STATUS:	//岩を押す2
		ChangeAnim(15);
		m_pD3dxMesh->m_hlAnimationList[15]->Speed = 0.015;
		break;

	case CLIMING_END_STATUS:
		ChangeAnim(16);
		m_pD3dxMesh->m_hlAnimationList[16]->Speed = 0.015;
		break;

	case SHIMMY_STATUS:
		ChangeAnim(17);
		m_pD3dxMesh->m_hlAnimationList[17]->Speed = 0.015;
		break;

	case SHIMMY_LEFT_STATUS:
		ChangeAnim(18);
		m_pD3dxMesh->m_hlAnimationList[18]->Speed = 0.015;
		break;

	case SHIMMY_RIGHT_STATUS:
		ChangeAnim(19);
		m_pD3dxMesh->m_hlAnimationList[19]->Speed = 0.015;
		break;

	case FALL_STATUS:
		ChangeAnim(20);
		m_pD3dxMesh->m_hlAnimationList[20]->Speed = 0.015;
		break;

	default:					//通常状態
		m_pD3dxMesh->m_hlAnimationList[2]->Speed = 0.009;
		ChangeAnim(2);
		break;
	}	
	assert((0 <= m_PlayerStatus && m_PlayerStatus <= 20)&& "XXX:ステータス番号以外の値が入っています");

	/*立ち上がる(最初のモーション)*/
	GettingUp();


	/*立ちアニメーションが終わったら通常状態に*/
	if (m_AnimFarstCount >= 48)
	{
		/*操作していない時は、常に通常状態に*/
		m_PlayerStatus = STANDING_STATUS;	
		m_AnimFarstCount = 52;
	}
	else
	{
		/*48フレーム以下なら立ち上がるモーション*/
		m_PlayerStatus = GETTING_UP_STATUS;
	}
	
	m_AnimFarstCount += 0.1;

	
	//アニメーションをストップ
	if (GetAsyncKeyState('G') && 0x8000)
	{
		m_pD3dxMesh->SetStop(TRUE);
	}
	//アニメーションを再生
	if (GetAsyncKeyState('B') && 0x8000)
	{
		m_pD3dxMesh->SetStop(FALSE);
	}
	
	

	//===============================================================
	//キャラクターの操作
	//===============================================================
	ToVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//if (GetAsyncKeyState('E') & 0x8000)	 //しゃがむ
	//{
	//	m_PlayerStatus = SQUAT_STATUS;
	//	squatStatusFlg = TRUE;
	//}
	//else { squatStatusFlg = FALSE; }

	if (squatStatusFlg == FALSE) //しゃがんでいなければ
	{
		JogForward();	//前進
		JogRight();		//右
		JogBack();		//後退
		JogLeft();		//左
		Running();		//走る
		RunningJump();	//ジャンプ-走っている時-
		Climing();		//上る
		ClimingDown();	//降りる
		
		CoverLeft();	//左壁歩き
		CoverRight();	//右壁歩き

		PushRock();		//岩を押す
		PushingRock();	//岩を押す2
		//ClimingEnd();	//崖を登り終える

		/*現在Lキーでぶら下がれる*/
		if (GetAsyncKeyState('L') && 0x8000)
		{
			m_ShimmyFlg = TRUE;
		}
		else
		{
			m_ShimmyFlg = FALSE;
		}

		Shimmy();		//ぶら下がる
		ShimmyLeft();	//ぶら下がり状態で左に動く
		ShimmyRight();	//ぶら下がり状態で右に動く

		if (GetAsyncKeyState('I') && 0x8000)
		{
			Fall();			//落ちる
		}
	


		///TODO : 常にyを下げていれば、ガクガクしない
		/*上の上がる(デバッグキー)*/
	//	if (GetAsyncKeyState('N') && 0x8000)
		{
			m_Pos.y -= 0.03;	//今はこれで対処
		}
		/*下に下がる(デバッグキー)*/
		if (GetAsyncKeyState('M') && 0x8000)
		{
			m_Pos.y += 0.03;
		}

		if (GetAsyncKeyState('K') && 0x8000)
		{
			chrRadian = 0.0f;
		}

		m_OperationPossible = TRUE;	
	}
	else//しゃがんでいれば
	{	
		SquadForward();	//前進
		SquadRight();	//右
		SquadBack();	//後退
		SquadLeft();	//左
	}
	
	
	/*プレイヤーとカメラ 内積と外積を使用*/
	//プレイヤーの周りをカメラが回ることができ、上キーは常にカメラからみて奥が全身とする
	if (m_PlayerStatus == JOGGING_STATUS || m_PlayerStatus == SQUAT_FORWARD_STATUS ||
		m_PlayerStatus == RUNNING_STATUS || m_PlayerStatus == JUMP_STATUS ) {

		D3DXVec3Normalize(&ToVec, &ToVec);//正規化
		
		D3DXVec3TransformNormal(&NowVec, &D3DXVECTOR3(0, 0, 1), &mRot);
		
		tmpRot = D3DXVec3Dot(&NowVec, &ToVec);
		tmpRot = D3DXToDegree(acos(tmpRot));
		if (tmpRot >= 0.1f) {
			assert((tmpRot >= 0.1f) && "XXX:不正な値です");

			D3DXVec3Normalize(&NowVec, &NowVec);
			D3DXVec3Cross(&vCross, &NowVec, &ToVec);
			D3DXVec3Normalize(&vCross, &vCross);
			if (tmpRot >= 10.0f)tmpRot = 10.0f;
			if (vCross.y > 0.9f) {
				chrRadian += tmpRot;
			}
			else if (vCross.y < -0.9f) {
				chrRadian -= tmpRot;
			}
			else {
				chrRadian += tmpRot;
			}
			D3DXMatrixRotationY(&mRot, D3DXToRadian(chrRadian));
			m_Yaw = D3DXToRadian(chrRadian);
		}
	}

	//===============================================================
	//角度をポジションに足す
	//===============================================================
	if (m_OperationPossible == TRUE)
	{
		Move();
	}
	



	//===============================================================
	//ジャンプ処理
	//===============================================================
	


	//===============================================================
	//落下処理
	//===============================================================
	if (m_PlayerStatus != CLIMING_STATUS)
	{
		m_Pos.y -= m_gravity;		//重力を自分にかけている
		m_gravity += 0.01;			//重力を増やしている
	}

	if (m_Pos.y <= -50)
	{
		m_Pos = D3DXVECTOR3(0, 0, 0);	//プレイヤーが落ちてしまったら強制的にPos(0,0,0)に
	}

	//===============================================================
	//地面との判定
	//===============================================================
	if (m_groundDis >= 0.0)
	{
		if (m_groundDis <= playerHeight)
		{
			m_Pos.y += (playerHeight - m_groundDis);
			m_gravity = 0.0f;
		}
	}



}
//
//
//
//
void Player::Move()
{
	if (m_Distance > 1.0f) {
		m_Pos += m_Dir;
	}
	
}

void Player::TransformNomalToVec(D3DXVECTOR3 _Dir)
{
	D3DXVec3TransformNormal(&tmpVec, &_Dir, &m_CamRad);
	m_Dir = ToVec += tmpVec;
}


void Player::CameraRotate()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		camRadian += 4.0f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		camRadian -= 4.0f;
	}
	D3DXMatrixRotationY(&m_CamRad, D3DXToRadian(camRadian));
	D3DXMatrixTranslation(&mTrans, m_Pos.x, m_Pos.y, m_Pos.z);
}





/*前進*/
void Player::JogForward()
{
	if (GetAsyncKeyState('W') & 0x8000) {		
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, move));

	}
}

/*右*/
void Player::JogRight()
{
	if (GetAsyncKeyState('D') & 0x8000) {		
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.06f, 0.0f, 0.0f));
	}
}
/*後退*/
void Player::JogBack()
{
	if (GetAsyncKeyState('S') & 0x8000) {		
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, -move));

	}
}

/*左*/
void Player::JogLeft()
{
	if (GetAsyncKeyState('A') & 0x8000) {	
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(-move, 0.0f, 0.0f));

	}
}


/*走る*/
void Player::Running()
{
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_PlayerStatus = RUNNING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, move + 0.02));
	}
}

/*登る*/
void Player::Climing()
{
	if (m_ClimingFlg == TRUE)
	{
		if (GetAsyncKeyState('C') & 0x8000)			
		{
			m_PlayerStatus = CLIMING_STATUS;
			TransformNomalToVec(D3DXVECTOR3(0.0f, 0.08f, 0.0f));
		}
		else
		{
			m_ClimingFlg = FALSE;
		}
	}
}

/*降りる*/
void Player::ClimingDown()
{

	if (GetAsyncKeyState('X') & 0x8000)			
	{
		m_PlayerStatus = CLIMING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, -0.04f, 0.0f));
	}
}

/*ジャンプ*/
void Player::RunningJump()
{
	if (m_PlayerStatus == RUNNING_STATUS)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)	
		{
			m_PlayerStatus = JUMP_STATUS;
			m_gravity = -0.1;

		}
	}
}

/*前進*/
void Player::SquadForward()
{
	if (GetAsyncKeyState('W') & 0x8000) {		
		m_PlayerStatus = SQUAT_FORWARD_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, 0.04f));
	}
}

/*右へ進む*/
void Player::SquadRight()
{
	if (GetAsyncKeyState('D') & 0x8000) {		
		m_PlayerStatus = SQUAT_RIGHT_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.04f, 0.0f, 0.0f));
	}
}

/*後ろに進む*/
void Player::SquadBack()
{
	if (GetAsyncKeyState('S') & 0x8000) {		
		m_PlayerStatus = SQUAT_BACK_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, -0.04f));

	}
}

/*左に進む*/
void Player::SquadLeft()
{
	if (GetAsyncKeyState('A') & 0x8000) {		
		m_PlayerStatus = SQUAT_LEFT_STATUS;
		TransformNomalToVec(D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
	}
}

/*弓を構える*/
void Player::BowReady()
{
	if (GetAsyncKeyState('Q') & 0x8000)				
	{
		m_PlayerStatus = BOW_READY_STATUS;

	}
}


/*左壁歩き*/
void Player::CoverLeft()
{
	if (m_CoverFlg == TRUE)
	{
		if (GetAsyncKeyState('T') & 0x8000)
		{
			m_PlayerStatus = COVER_LEFT_STATUS;
			TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, move-0.02));

		}
		else
		{
			m_CoverFlg = FALSE;
		}
	}
	
	
}

/*右壁歩き*/
void Player::CoverRight()
{

	/*if (m_CoverFlg == TRUE)
	{
		if (GetAsyncKeyState('Y') & 0x8000)
		{
			m_PlayerStatus = COVER_RIGHT_STATUS;

		}
		else
		{
			m_CoverFlg = FALSE;
		}
	}	*/
}

/*立ちあがる*/
void Player::GettingUp()
{

	if (GetAsyncKeyState('F') && 0x8000)
	{
		m_PlayerStatus = GETTING_UP_STATUS;
	}
}


/*岩を押す*/
void Player::PushRock()
{
	if (m_PushRockFlg == TRUE)
	{

		if (m_PushNow == FALSE)
		{
			if (GetAsyncKeyState('E') && 0x8000)
			{
				m_PushNow = TRUE;
				//TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, 0.01f));
			}
		}
		
	}

	if (m_PushNow == TRUE)
	{
		m_PlayerStatus = PUSH_ROCK_STATUS;
	}


	if (GetAsyncKeyState('U') && 0x8000)
	{
		m_PushNow = FALSE;
	}

}

/*岩を押す2*/
void Player::PushingRock()
{
	if (m_PushinFlg == TRUE)
	{
		m_PlayerStatus = PUSHING_ROCK_STATUS;
	}
	
}

/*崖を登り終える*/
void Player::ClimingEnd()
{

	if (m_ClimeEndFlg == TRUE)
	{
		if (m_ClimeEndCount <= 22)
		{
			m_PlayerStatus = CLIMING_END_STATUS;
		}
		else
		{
			m_ClimeEndFlg = FALSE;
		}
		m_ClimeEndCount += 0.1;
		
	}
	
	
}

void Player::Shimmy()
{
	if (m_ShimmyFlg == TRUE)
	{
		m_PlayerStatus = SHIMMY_STATUS;
	}
}

void Player::ShimmyLeft()
{
	if (m_ShimmyFlg == TRUE && GetAsyncKeyState('A'))
	{
		m_PlayerStatus = SHIMMY_LEFT_STATUS;
	}

}

void Player::ShimmyRight()
{
	if (m_ShimmyFlg == TRUE && GetAsyncKeyState('D'))
	{
		m_PlayerStatus = SHIMMY_RIGHT_STATUS;
	}
}

void Player::Fall()
{
	m_PlayerStatus = FALL_STATUS;
}