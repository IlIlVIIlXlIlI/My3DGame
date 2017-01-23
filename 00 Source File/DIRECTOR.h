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
		�Q�[���̃V�[��
		*/
		INIT_OPENING,	//0 : ������(�I�[�v�j���O)

		OPENING,		//1 : �I�[�v�j���O

		INIT_STAGE1,	//2 : ������(�X�e�[�W1)

		PLAY_STAGE1,	//3 : �X�e�[�W1

		PLAY_STAGE2,	//4 : �X�e�[�W2

		WIN,			//5 : ����

		GAMEOVER,		//6 : �Q�[���I��
	};


	//Resorce��Shared_ptr
	//���̑��̃|�C���^��unique_ptr

	//Data
	HINSTANCE					m_hInstance;
	HWND						m_hWnd;
	SCENE						m_Scene;
	unique_ptr<WINDOW>			m_pWindow;
	unique_ptr<DIRECT3D11>		m_pD3d;
	unique_ptr<CAMERA>			m_pCamera;
	shared_ptr<SOUND>			m_pSound;
	//=============================================================
	//�X�^�e�B�b�N���b�V��	
	//=============================================================
	shared_ptr<CD3DXMESH>		m_pMap_Start;			//�t�B�[���h
	shared_ptr<CD3DXMESH>		m_pMap_Start_Col;		//�t�B�[���h1�̃R���W�������f��
	shared_ptr<CD3DXMESH>		m_pSkyBox;				//��
	shared_ptr<CD3DXMESH>		m_pMoveRock;			//��
	shared_ptr<CD3DXMESH>		m_pOpenRock;			//�J����
	shared_ptr<CD3DXMESH>		m_pPillar;
	
	//=============================================================
	//DEBUG STRING
	//=============================================================
#ifdef _DEBUG
	unique_ptr<D3D11_TEXT>		m_pText;
#endif
	//=============================================================
	//�X�v���C�g�̍쐬
	//=============================================================

	/*�^�C�g���Ŏg��*/
	unique_ptr<SPRITE>			m_pTitle;
	unique_ptr<SPRITE>			m_pPressEnter;
	unique_ptr<SPRITE>			m_pExit;
	unique_ptr<SPRITE>			m_pTitlePlayer;
	unique_ptr<SPRITE>			m_pFadeIn;

	/*�{�҂Ŏg��*/
	unique_ptr<SPRITE>			m_pBlackBar;
	unique_ptr<SPRITE>			m_pUpdateLabel;
	unique_ptr<SPRITE>			m_pEscapeRoot;
	unique_ptr<SPRITE>			m_pElseRoot;
	//=============================================================
	//X�X�L�����b�V���A�j���[�V�����̍쐬
	//=============================================================
	shared_ptr<Player>			m_pPlayer;
	CD3DXMESH*					m_pPlayerSphere;

	//=============================================================
	//�����蔻��
	//=============================================================
	unique_ptr<COLLISION>		m_pCollision;
	


	//=============================================================
	//�X�t�B�A�̓����蔻��
	//=============================================================
	//CD3DXMESH*					m_pSphereMesh;				//�{���̃X�t�B�A
	shared_ptr<CD3DXMESH>			m_pSphereMesh;


	CD3DXMESH*					m_pMoveRock_Sphere1;		//��̃X�t�B�A
	CD3DXMESH*					m_pCliff_Sphere2;			//�R�����̃X�t�B�A
	CD3DXMESH*					m_pCliff_Sphere3;			//�R��n��̃X�t�B�A
	shared_ptr<CD3DXMESH>		m_pCave_Sphere4;			//���A�̃X�t�B�A
	shared_ptr<CD3DXMESH>		m_pDropAndOpenRock5;		//�����Ă����ƊJ����X�t�B�A
	shared_ptr<CD3DXMESH>		m_pClimeEndSphere6;			//�R��o��I����
	shared_ptr<CD3DXMESH>		m_pShimmyShpere7;
	//=============================================================
	//���Ƃ̓����蔻��
	//=============================================================
	HRESULT InitSphere(CD3DXMESH*);
	bool Collision(CD3DXMESH*, CD3DXMESH*);



	//=============================================================
	//������J�����O(View Frustum)
	//=============================================================
	shared_ptr<Frustum>			m_pViewFrustum;

	//=============================================================
	//E�L�[(�v�b�V��)
	//=============================================================
	shared_ptr<SPRITE>			m_keyE;
	shared_ptr<SPRITE>			m_keyE2;
	shared_ptr<SPRITE>			m_keyC;

	//=============================================================
	//Update�̃��x��
	//=============================================================
	unique_ptr<LABELCAL>		m_LabelCal;


	//=============================================================
	//BrackBar�̃��x��
	//=============================================================
	unique_ptr<BLACKBAR>		m_BB;

public:
	//Method
	DIRECTOR();
	~DIRECTOR();
	HRESULT		Init();
	void		Run(HINSTANCE);
	void		MainLoop();			//��ԑ厖�ȃ��[�v
	void		FixFPS60();			//60FPS
	HRESULT		InitOpening();		//������(�I�[�v�j���O)
	void		Opening();			//�I�[�v�j���O
	HRESULT		InitStage1();		//������(�X�e�[�W1)
	void		Stage1();			//�X�e�[�W1

	float count;
	

	void objToSphere(CD3DXMESH*,CD3DXMESH*);



};

