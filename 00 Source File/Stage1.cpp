#include "DIRECTOR.h"
#include <iostream>
using namespace std;
/*
MEMO

TODO : ��Ŏ��t����

FIX	 : ���m�̕s��̂���R�[�h

HACK : ���܂肫�ꂢ����Ȃ�������

XXX  : �댯! �傫�Ȗ�肪����

*/


void DIRECTOR::Stage1()
{
	//�}���`�X���b�h
	//GET_THREAD.Update();

	
	///TODO : �����蔻����ȗ�������

	/*�n�`�Ƃ̋����𑪂�*/
	m_pPlayer->m_Distance = m_pCollision->RayGetDistance(m_hWnd,m_pPlayer.get(), m_pMap_Start_Col.get());
	//m_pPlayer->m_Distance = m_pCollision->RayGetDistance(m_hWnd, m_pPlayer.get(), m_pMoveRock.get());

	/*�n�ʂƂ̓����蔻��*/
	m_pCollision->RayIntersectDown(m_pPlayer.get(),m_pMap_Start.get(),&m_pPlayer->m_groundDis);

	
	//==============================================================================================
	//Camera 
	//==============================================================================================
	
	/*�ǂ��߂Â��ƃv���C���[�ɐڋ߂���J����*/
	//D3DXVECTOR3 Start = D3DXVECTOR3(0, 1.5, 0);//
	//D3DXVECTOR3 End = D3DXVECTOR3(0, 1.7, -4);
	//D3DXVec3TransformCoord(&Start, &Start, &m_pPlayer->mTrans);
	//D3DXVec3TransformCoord(&End, &End, &m_pPlayer->mTrans);
	//D3DXVECTOR3 EyePt = m_pCamera->GetRayDistance(m_pMap_Start_Col.get(),Start, End); //�J�����i���_�j�ʒu
	//D3DXVECTOR3 LookatPt = Start;//�����ʒu
	//D3DXVECTOR3 UpVec(0.0f, 1.0f, 0.0f);//����ʒu


	//D3DXMatrixLookAtLH(&mView, &EyePt, &LookatPt, &UpVec);


	///TODO : �J�������ȗ�������
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


	/*�����_�ݒ�*/
	m_pCamera->CLook = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformCoord(&m_pCamera->CLook, &m_pCamera->CLook, &m_pPlayer->mTrans);

	/*��������ݒ�*/
	D3DXVECTOR3 CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	/*���_�s��̐ݒ�*/
	D3DXMatrixLookAtLH(&mView, &m_pCamera->mCPos, &m_pCamera->CLook, &CHead);

	/*�v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j*/
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);


	

	//==============================================================================================
	//�X�V
	//==============================================================================================

	/*�v���C���[*/
	m_pPlayer->Player::Update();

	
	/*�J����*/
	m_pCamera->Update();


	//==============================================================================================
	//Render
	//==============================================================================================
	static bool openRockFlg = TRUE;
	/*��*/
	m_pSkyBox->m_fYaw += 0.0001;
	m_pSkyBox->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	/*�}�b�v*/
	m_pMap_Start->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
	//m_pMap_Start_Col->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	/*�v���C���[(�{��)*/
	m_pPlayer->CD3DXSKINMESH::Render(mView, mProj, D3DXVECTOR3(0, -1, 0), m_pCamera->CLook);
	

	/*���������(�{��)*/
	m_pMoveRock->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);


	/*�J����*/
	if (openRockFlg == TRUE)
	{
		m_pOpenRock->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
	}
	

	//m_pCave_Sphere4->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	//==============================================================================================
	//Render(Sphere)
	//==============================================================================================

	/*�j�Z���m�̃X�t�B�A(�v���C���[�Ɠ����W�̋�)*/
	m_pPlayerSphere->m_Pos = m_pPlayer->m_Pos;
	m_pPlayerSphere->m_Pos.y = m_pPlayer->m_Pos.y + 0.5;
	///m_pPlayerSphere->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);

	/*�v���C���[�̃X�t�B�A������*/
	if (GetAsyncKeyState('1') && 0x8000)
	{
		m_pSphereMesh->m_Pos = m_pPlayerSphere->m_Pos;		//�v���C���[�̍��W��{���̃X�t�B�A�ɓ����
		m_pSphereMesh->m_fScale = m_pPlayerSphere->m_Sphere.Radius * 2;
		m_pSphereMesh->Render(mView, mProj, D3DXVECTOR3(0, 1, -1), m_pCamera->CLook);

#ifdef _DEBUG
		std::cout << "�v���C���[�̖{���̃X�t�B�A��`��" << std::endl;
#endif
	}
	
	static bool sphereVisibility = FALSE;
	/*����������E�L�[�X�t�B�A1*/
	objToSphere(m_pMoveRock_Sphere1,m_pSphereMesh.get());
		
	/*����������E�L�[�X�t�B�A2*/
	objToSphere(m_pCliff_Sphere2, m_pSphereMesh.get());

	/*�R��n��X�t�B�A3*/
	objToSphere(m_pCliff_Sphere3, m_pSphereMesh.get());
	
	/*���������X�t�B�A4*/
	objToSphere(m_pCave_Sphere4.get(), m_pSphereMesh.get());

	/*�����Ă����ƊJ���X�t�B�A5*/
	objToSphere(m_pDropAndOpenRock5.get(), m_pSphereMesh.get());

	/*�o��I�����Ƃ��̃X�t�B�A6*/
	objToSphere(m_pClimeEndSphere6.get(), m_pSphereMesh.get());

	/*�Ԃ牺����ӏ��̃X�t�B�A7*/
	objToSphere(m_pShimmyShpere7.get(), m_pSphereMesh.get());


	/*2�L�[�ŃX�t�B�A����*/
	if (GetAsyncKeyState('2') && 0x8000)
	{
		if (sphereVisibility == FALSE)
		{
			///*��𓮂������߂̃X�t�B�A������*/
			m_pMoveRock_Sphere1->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*�R��o�邽�߂̃X�t�B�A������*/
			m_pCliff_Sphere2->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*�R��n�邽�߂̃X�t�B�A������*/
			m_pCliff_Sphere3->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*��������邽�߂̃X�t�B�A������*/
			m_pCave_Sphere4->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*�����Ă����ƊJ���X�t�B�A������*/
			m_pDropAndOpenRock5->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*�o��I����X�t�B�A������*/
			m_pClimeEndSphere6->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
			///*�Ԃ牺����X�t�B�A������*/
			m_pShimmyShpere7->Render(mView, mProj, D3DXVECTOR3(0, 1, 0), m_pCamera->CLook);
		}
	}
	else
	{
		sphereVisibility = FALSE;
	}


	//==============================================================================================
	//�X�t�B�A�Ƃ̏Փ˔���
	//==============================================================================================
	static BOOL KeyFlg = FALSE;
	//�X�t�B�A�ɓ������Ă��邩
	static bool moveRockStartFlg = FALSE;
	/*�v���C���[�̃X�t�B�A�Ɗ�̂����蔻��*/
	if (Collision(m_pPlayerSphere, m_pMoveRock_Sphere1))
	{

		SetWindowTextA(m_hWnd, "�Փ˂��Ă��܂�");

		//�L�[�̘A�ł�8.0f�ȉ�
		if (m_pPlayer->KeyPanch <= 8.0f)
		{
			/*E�L�[�X�v���C�g*/
			m_keyE->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);


			m_pPlayer->m_PushRockFlg = TRUE;

			/*���уX�v���C�g*/
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
			m_pPlayer->m_PushRockFlg = FALSE;	//�������Ă��Ȃ�
			m_pPlayer->m_PushinFlg = FALSE;		//����������ł��Ȃ�
			m_pPlayer->m_PushNow = FALSE;		//�������Ă��Ȃ�

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


	/*�N���C�~���O*/
	if (Collision(m_pPlayerSphere, m_pCliff_Sphere2))
	{
		SetWindowTextA(m_hWnd, "�Փ˂��Ă��܂�");
		m_pPlayer->m_ClimingFlg = TRUE;
		/*C�L�[�X�v���C�g*/
		m_keyC->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);
	}
	
	/*�Ǖ���*/
	if (Collision(m_pPlayerSphere, m_pCliff_Sphere3))
	{
		SetWindowTextA(m_hWnd, "�Փ˂��Ă��܂�");
		m_pPlayer->m_CoverFlg = TRUE;
		/*E�L�[�X�v���C�g*/
		m_keyE->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);
	}


	/*�₭����*/
	if (Collision(m_pPlayerSphere, m_pCave_Sphere4.get()))
	{
		SetWindowTextA(m_hWnd, "�Փ˂��Ă��܂�");

		if (GetAsyncKeyState('E') && 0x8000)
		{
			m_pPlayer->squatStatusFlg = TRUE;
		}

		/*E�L�[�X�v���C�g*/
		m_keyE->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) - 40, (WINDOW_HEIGHT / 2) + 80, 0),1.0f);
	}

	static bool moveRockFlg = 0;
	static float moveRockDrop = 40.0;
	/*�����Ă����ƊJ��*/
	if (Collision(m_pPlayerSphere, m_pDropAndOpenRock5.get()))
	{
		SetWindowTextA(m_hWnd, "�Փ˂��Ă��܂�");	
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

	/*�R��o��I����*/
	/*if (GetAsyncKeyState('L') && 0x8000)
	{
		m_pPlayer->m_ClimeEndFlg = TRUE;
	}*/
	/*if (Collision(m_pPlayerSphere,m_pClimeEndSphere6.get()))
	{
		SetWindowTextA(m_hWnd, "�����œo��I�����I");
		m_pPlayer->m_ClimeEndFlg = TRUE;
	}

	if (m_pPlayer->m_ClimeEndCount >= 30)
	{
		m_pPlayer->m_Pos = D3DXVECTOR3(1.0f, 14.6f, 36.2f);
	}*/


	/*�Ԃ牺����X�t�B�A�Ƃ̓����蔻��*/
	if (Collision(m_pPlayerSphere, m_pShimmyShpere7.get()))
	{

	}
	//==============================================================================================
	//������J�����O
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

	/*Update���x��*/
	
	

	/*�A�b�v�f�[�g���x����`��*/
	m_pUpdateLabel->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) + m_LabelCal->markCount, WINDOW_HEIGHT / 2, 0), 0.5);
	
	/*�A�b�v�f�[�g���x���̏o�����v�Z*/
	m_LabelCal->UpdateLabel();

	
	/*���x���̕\���̎d�����v�Z*/
	m_LabelCal->MissionLabel();
	



	if (openRockFlg == FALSE)
	{
		/*�ʃ��[�g��T��*/
		m_pElseRoot->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) + m_LabelCal->labelCount, (WINDOW_HEIGHT / 2) + 30, 0), 0.5);
	}
	else
	{
		/*�E�o���[�g��T��*/
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
	//�f�o�b�O�L�[
	//==================
	//�ǉ������̏ꏊ�܂Ń��[�v
	if (GetAsyncKeyState('H') && 0x8000)
	{
		m_pPlayer->m_Pos = D3DXVECTOR3(-77.9, 6.8, 122.5);
	}
	//==================
	//���C�̕`��
	//==================
	m_pPlayer->RenderRay(mView, mProj, D3DXVECTOR3(0, 0, 1), RAY_DISTANCE);


#endif

	
}

/*�I�u�W�F�N�g�̈ʒu�ɃX�t�B�A�̈ʒu������*/
void DIRECTOR::objToSphere(CD3DXMESH* _pObj, CD3DXMESH* _Sphere)
{
	_Sphere->m_Pos = _pObj->m_Pos;
	_Sphere->m_Pos.y = _pObj->m_Pos.y + 0.5;
	_Sphere->m_fScale = _pObj->m_Sphere.Radius * 2;
}


