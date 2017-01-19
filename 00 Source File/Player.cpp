#include "Player.h"


Player::Player()
{
	move = 0.06;						//�ړ���

	m_Dir = D3DXVECTOR3(0, 0, 1);		//����
	
	m_Pos = D3DXVECTOR3(0, 0, 0);		//���W
			
	m_Scale = D3DXVECTOR3(1, 1, 1);		//�g��s��

	/*���삵�Ă��Ȃ����́A��ɒʏ��Ԃ�*/
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
	//�J�����̉�]
	//===============================================================
	CameraRotate();
	

	//MEMO (���A���^�C���ŏ�������)
	//0 : ���Ⴊ��
	//1 : ����
	//2 : �ʏ�(����)
	//3 : ���Ⴊ��(�O�ɓ���)
	//4 : ���Ⴊ��(�E�ɓ���)
	//5 : ���Ⴊ��(���ɓ���)
	//6 : ���Ⴊ��(���ɓ���)
	//7 : �|���\����
	//8 : �����j���O
	//9 : �N���C�~���O(UP)
	//10: �W�����v
	//===============================================================
	//�L�����N�^�[�̏�ԕω�
	//===============================================================

	///TODO : State�p�^�[���ɒu��������

	switch (m_PlayerStatus)
	{
	case SQUAT_STATUS:	
		ChangeAnim(0);		//���Ⴊ��
		m_pD3dxMesh->m_hlAnimationList[0]->Speed = 0.020;
		break;

	case JOGGING_STATUS:		//�W���M���O
		ChangeAnim(1);
		m_pD3dxMesh->m_hlAnimationList[1]->Speed = 0.020;
		break;

	case SQUAT_FORWARD_STATUS:	//���Ⴊ��(�O�ɓ���)
		ChangeAnim(3);
		m_pD3dxMesh->m_hlAnimationList[3]->Speed = 0.020;
		break;

	case SQUAT_RIGHT_STATUS:	//���Ⴊ��(�E�ɓ���)
		ChangeAnim(4);
		m_pD3dxMesh->m_hlAnimationList[4]->Speed = 0.020;
		break;

	case SQUAT_BACK_STATUS:		//���Ⴊ��(���ɓ���)
		ChangeAnim(5);
		m_pD3dxMesh->m_hlAnimationList[5]->Speed = 0.020;
		break;

	case SQUAT_LEFT_STATUS:		//���Ⴊ��(���ɓ���)
		ChangeAnim(6);
		m_pD3dxMesh->m_hlAnimationList[6]->Speed = 0.020;
		break;

	case BOW_READY_STATUS:		//�|���\����
		ChangeAnim(7);
		m_pD3dxMesh->m_hlAnimationList[7]->Speed = 0.020;
		break;

	case RUNNING_STATUS:		//�����j���O
		ChangeAnim(8);
		m_pD3dxMesh->m_hlAnimationList[8]->Speed = 0.015;
		break;

	case CLIMING_STATUS:		//�N���C�~���O(UP)
		ChangeAnim(9);
		m_pD3dxMesh->m_hlAnimationList[9]->Speed = 0.020;
		break;

	case JUMP_STATUS:			//�W�����v
		ChangeAnim(10);
		m_pD3dxMesh->m_hlAnimationList[10]->Speed = 0.015;
		break;

	case COVER_LEFT_STATUS:		//���Ǖ���
		ChangeAnim(11);
		m_pD3dxMesh->m_hlAnimationList[11]->Speed = 0.012;
		break;

	case COVER_RIGHT_STATUS:	//�E�Ǖ���
		ChangeAnim(12);
		m_pD3dxMesh->m_hlAnimationList[12]->Speed = 0.012;
		break;

	case GETTING_UP_STATUS:		//�����オ��(�ŏ��̃��[�V����)
		ChangeAnim(13);
		m_pD3dxMesh->m_hlAnimationList[13]->Speed = 0.015;
		break;

	case PUSH_ROCK_STATUS:		//�������
		ChangeAnim(14);
		m_pD3dxMesh->m_hlAnimationList[14]->Speed = 0.015;
		break;

	case PUSHING_ROCK_STATUS:	//�������2
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

	default:					//�ʏ���
		m_pD3dxMesh->m_hlAnimationList[2]->Speed = 0.009;
		ChangeAnim(2);
		break;
	}	
	assert((0 <= m_PlayerStatus && m_PlayerStatus <= 20)&& "XXX:�X�e�[�^�X�ԍ��ȊO�̒l�������Ă��܂�");

	/*�����オ��(�ŏ��̃��[�V����)*/
	GettingUp();


	/*�����A�j���[�V�������I�������ʏ��Ԃ�*/
	if (m_AnimFarstCount >= 48)
	{
		/*���삵�Ă��Ȃ����́A��ɒʏ��Ԃ�*/
		m_PlayerStatus = STANDING_STATUS;	
		m_AnimFarstCount = 52;
	}
	else
	{
		/*48�t���[���ȉ��Ȃ痧���オ�郂�[�V����*/
		m_PlayerStatus = GETTING_UP_STATUS;
	}
	
	m_AnimFarstCount += 0.1;

	
	//�A�j���[�V�������X�g�b�v
	if (GetAsyncKeyState('G') && 0x8000)
	{
		m_pD3dxMesh->SetStop(TRUE);
	}
	//�A�j���[�V�������Đ�
	if (GetAsyncKeyState('B') && 0x8000)
	{
		m_pD3dxMesh->SetStop(FALSE);
	}
	
	

	//===============================================================
	//�L�����N�^�[�̑���
	//===============================================================
	ToVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//if (GetAsyncKeyState('E') & 0x8000)	 //���Ⴊ��
	//{
	//	m_PlayerStatus = SQUAT_STATUS;
	//	squatStatusFlg = TRUE;
	//}
	//else { squatStatusFlg = FALSE; }

	if (squatStatusFlg == FALSE) //���Ⴊ��ł��Ȃ����
	{
		JogForward();	//�O�i
		JogRight();		//�E
		JogBack();		//���
		JogLeft();		//��
		Running();		//����
		RunningJump();	//�W�����v-�����Ă��鎞-
		Climing();		//���
		ClimingDown();	//�~���
		
		CoverLeft();	//���Ǖ���
		CoverRight();	//�E�Ǖ���

		PushRock();		//�������
		PushingRock();	//�������2
		//ClimingEnd();	//�R��o��I����

		/*����L�L�[�łԂ牺�����*/
		if (GetAsyncKeyState('L') && 0x8000)
		{
			m_ShimmyFlg = TRUE;
		}
		else
		{
			m_ShimmyFlg = FALSE;
		}

		Shimmy();		//�Ԃ牺����
		ShimmyLeft();	//�Ԃ牺�����Ԃō��ɓ���
		ShimmyRight();	//�Ԃ牺�����ԂŉE�ɓ���

		if (GetAsyncKeyState('I') && 0x8000)
		{
			Fall();			//������
		}
	


		///TODO : ���y�������Ă���΁A�K�N�K�N���Ȃ�
		/*��̏オ��(�f�o�b�O�L�[)*/
	//	if (GetAsyncKeyState('N') && 0x8000)
		{
			m_Pos.y -= 0.03;	//���͂���őΏ�
		}
		/*���ɉ�����(�f�o�b�O�L�[)*/
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
	else//���Ⴊ��ł����
	{	
		SquadForward();	//�O�i
		SquadRight();	//�E
		SquadBack();	//���
		SquadLeft();	//��
	}
	
	
	/*�v���C���[�ƃJ���� ���ςƊO�ς��g�p*/
	//�v���C���[�̎�����J��������邱�Ƃ��ł��A��L�[�͏�ɃJ��������݂ĉ����S�g�Ƃ���
	if (m_PlayerStatus == JOGGING_STATUS || m_PlayerStatus == SQUAT_FORWARD_STATUS ||
		m_PlayerStatus == RUNNING_STATUS || m_PlayerStatus == JUMP_STATUS ) {

		D3DXVec3Normalize(&ToVec, &ToVec);//���K��
		
		D3DXVec3TransformNormal(&NowVec, &D3DXVECTOR3(0, 0, 1), &mRot);
		
		tmpRot = D3DXVec3Dot(&NowVec, &ToVec);
		tmpRot = D3DXToDegree(acos(tmpRot));
		if (tmpRot >= 0.1f) {
			assert((tmpRot >= 0.1f) && "XXX:�s���Ȓl�ł�");

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
	//�p�x���|�W�V�����ɑ���
	//===============================================================
	if (m_OperationPossible == TRUE)
	{
		Move();
	}
	



	//===============================================================
	//�W�����v����
	//===============================================================
	


	//===============================================================
	//��������
	//===============================================================
	if (m_PlayerStatus != CLIMING_STATUS)
	{
		m_Pos.y -= m_gravity;		//�d�͂������ɂ����Ă���
		m_gravity += 0.01;			//�d�͂𑝂₵�Ă���
	}

	if (m_Pos.y <= -50)
	{
		m_Pos = D3DXVECTOR3(0, 0, 0);	//�v���C���[�������Ă��܂����狭���I��Pos(0,0,0)��
	}

	//===============================================================
	//�n�ʂƂ̔���
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





/*�O�i*/
void Player::JogForward()
{
	if (GetAsyncKeyState('W') & 0x8000) {		
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, move));

	}
}

/*�E*/
void Player::JogRight()
{
	if (GetAsyncKeyState('D') & 0x8000) {		
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.06f, 0.0f, 0.0f));
	}
}
/*���*/
void Player::JogBack()
{
	if (GetAsyncKeyState('S') & 0x8000) {		
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, -move));

	}
}

/*��*/
void Player::JogLeft()
{
	if (GetAsyncKeyState('A') & 0x8000) {	
		m_PlayerStatus = JOGGING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(-move, 0.0f, 0.0f));

	}
}


/*����*/
void Player::Running()
{
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_PlayerStatus = RUNNING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, move + 0.02));
	}
}

/*�o��*/
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

/*�~���*/
void Player::ClimingDown()
{

	if (GetAsyncKeyState('X') & 0x8000)			
	{
		m_PlayerStatus = CLIMING_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, -0.04f, 0.0f));
	}
}

/*�W�����v*/
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

/*�O�i*/
void Player::SquadForward()
{
	if (GetAsyncKeyState('W') & 0x8000) {		
		m_PlayerStatus = SQUAT_FORWARD_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, 0.04f));
	}
}

/*�E�֐i��*/
void Player::SquadRight()
{
	if (GetAsyncKeyState('D') & 0x8000) {		
		m_PlayerStatus = SQUAT_RIGHT_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.04f, 0.0f, 0.0f));
	}
}

/*���ɐi��*/
void Player::SquadBack()
{
	if (GetAsyncKeyState('S') & 0x8000) {		
		m_PlayerStatus = SQUAT_BACK_STATUS;
		TransformNomalToVec(D3DXVECTOR3(0.0f, 0.0f, -0.04f));

	}
}

/*���ɐi��*/
void Player::SquadLeft()
{
	if (GetAsyncKeyState('A') & 0x8000) {		
		m_PlayerStatus = SQUAT_LEFT_STATUS;
		TransformNomalToVec(D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
	}
}

/*�|���\����*/
void Player::BowReady()
{
	if (GetAsyncKeyState('Q') & 0x8000)				
	{
		m_PlayerStatus = BOW_READY_STATUS;

	}
}


/*���Ǖ���*/
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

/*�E�Ǖ���*/
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

/*����������*/
void Player::GettingUp()
{

	if (GetAsyncKeyState('F') && 0x8000)
	{
		m_PlayerStatus = GETTING_UP_STATUS;
	}
}


/*�������*/
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

/*�������2*/
void Player::PushingRock()
{
	if (m_PushinFlg == TRUE)
	{
		m_PlayerStatus = PUSHING_ROCK_STATUS;
	}
	
}

/*�R��o��I����*/
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