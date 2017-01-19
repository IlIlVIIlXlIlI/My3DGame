#include "DIRECTOR.h"

/*
MEMO

TODO : ��Ŏ��t����

FIX	 : ���m�̕s��̂���R�[�h

HACK : ���܂肫�ꂢ����Ȃ�������

XXX  : �댯! �傫�Ȗ�肪����

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
	//�X�v���C�g�̍쐬
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
	//���b�V���ǂݍ���
	//==========================================================================
	//�}�b�v
	SetVisualDirectory();
	m_pMap_Start = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Start.x");


	//�}�b�v�̃R���W�������f��
	SetVisualDirectory();
	m_pMap_Start_Col = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Start_Col.x");

	//��̃��f��
	SetVisualDirectory();
	m_pSkyBox = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sky.x");
	m_pSkyBox->m_fScale = 3.0f;

	//���������̃��f��
	SetVisualDirectory();
	m_pMoveRock = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"moveRock.x");

	//�J����
	SetVisualDirectory();
	m_pOpenRock = make_shared<CD3DXMESH>
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"OpenRock.x");
	//============================================================================
	//�����蔻��p�̃X�t�B�A
	//============================================================================

	//���������
	SetVisualDirectory();
	m_pMoveRock_Sphere1 = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pMoveRock_Sphere1->m_Pos = D3DXVECTOR3(1.0f, 0.0f, 21.0f);
	/*�X�t�B�A�����(���������)*/
	InitSphere(m_pMoveRock_Sphere1);



	//����R
	SetVisualDirectory();
	m_pCliff_Sphere2 = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pCliff_Sphere2->m_Pos = D3DXVECTOR3(1,0,35.0);
	/*�X�t�B�A�����(����R)*/
	InitSphere(m_pCliff_Sphere2);


	//�n���R
	SetVisualDirectory();
	m_pCliff_Sphere3 = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pCliff_Sphere3->m_Pos = D3DXVECTOR3(-77.7f, 7.0f, 122.9);
	/*�X�t�B�A�����(�n���R)*/
	InitSphere(m_pCliff_Sphere3);



	//������		
	SetVisualDirectory();
	m_pCave_Sphere4 = make_shared<CD3DXMESH>();
	m_pCave_Sphere4->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pCave_Sphere4->m_Pos = D3DXVECTOR3(-74.8f, 6.8f, 186.0f);


	//�����Ă����ƊJ����
	SetVisualDirectory();
	m_pDropAndOpenRock5 = make_shared<CD3DXMESH>();
	m_pDropAndOpenRock5->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pDropAndOpenRock5->m_Pos = D3DXVECTOR3(0.5f, 16.0f, 109.097f);


	//�R��o��I����
	SetVisualDirectory();
	m_pClimeEndSphere6 = make_shared<CD3DXMESH>();
	m_pClimeEndSphere6->Init(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pClimeEndSphere6->m_Pos = D3DXVECTOR3(1.0f, 12.0f, 35.0f);


	//============================================================================
	//SKINMESH
	//============================================================================
	//�v���C���[
	SetVisualDirectory();
	m_pPlayer = make_shared<Player>();
	m_pPlayer->InitSM(m_hWnd, DEVICE, DCONTEXT);
	m_pPlayer->CreateFromX("player21.x");




	//�j�Z���m�̃X�t�B�A
	SetVisualDirectory();
	m_pPlayerSphere = new CD3DXMESH
		(m_hWnd, DEVICE, DCONTEXT, (LPSTR)"Sphere.x");
	m_pPlayerSphere->m_Pos = m_pPlayer->m_Pos;

	/*�X�t�B�A�����(�v���C���[)*/
	InitSphere(m_pPlayerSphere);


	

	//============================================================================
	//�L�[�v�b�V��
	//============================================================================
	/*E�L�[*/
	SetRootDirectory();
	m_keyE = make_shared<SPRITE>
		(DCONTEXT, (LPSTR)"E_KEY.png", 94, 92);
	
	/*C�L�[*/
	SetRootDirectory();
	m_keyC = make_shared<SPRITE>
		(DCONTEXT, (LPSTR)"C_KEY.png", 94, 92);

	//=============================================================
	//Update���x��
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
	MFAIL(m_pSound->Init(), "�T�E���h���������s");

	//============================================================================
	//�T�E���h�ǂݍ���
	//============================================================================
	SetSoundDirectory();
	m_pSound->LoadSound("Paranomal_2.wav");



	//============================================================================
	//�V�[�����X�e�[�W1��
	//============================================================================
	m_Scene = PLAY_STAGE1;

	return S_OK;
}