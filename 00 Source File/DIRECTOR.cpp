#include "DIRECTOR.h"


 
//
DIRECTOR::DIRECTOR()
{
	/*
	�����V�[�����X�e�[�W1��
	*/
	ZeroMemory(this,sizeof(DIRECTOR));
	m_Scene = INIT_OPENING;
	count = 0.0f;
}
//
//
///HACK : �X�}�[�g�|�C���^�ɒu�����������ߍ��͕K�v�Ȃ�
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
	// ���b�Z�[�W���[�v
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
		assert(!"XXX:�s���ȃQ�[���X�e�[�^�X�ł�");

	}
	

	FixFPS60();
	m_pD3d->Present();
}
//
//
//
HRESULT DIRECTOR::Init()
{
	/*Window�̍쐬*/
	m_pWindow= make_unique<WINDOW>();

	if(!m_pWindow)
	{
		return E_FAIL;
	}
	MFAIL(m_pWindow->InitWindow(m_hInstance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME), "�E�B���h�E");
	m_hWnd=m_pWindow->m_hWnd;
	
	/*DircetX11*/
	D3D_INIT di;
	m_pD3d= make_unique<DIRECT3D11>();

	
	/*DirectX11�̏��������s���ǂ���*/
	if(m_pD3d==nullptr)
	{
		MSG("Direct3D�̏��������s");
		return E_FAIL;
	}

	di.hWnd = m_hWnd;
	MFAIL(m_pD3d->Init(&di),"Direct3D���������s");


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
		assert((Time <= 16.6666), "XXX:�s���Ȑ��l�ł�");
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

	//���b�V���̒��_�o�b�t�@�[�����b�N����
	if (FAILED(pMesh->m_pMesh->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}
	// ���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����
	D3DXComputeBoundingSphere((D3DXVECTOR3*)pVertices, pMesh->m_pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(pMesh->m_pMesh->GetFVF()), &vCenter, &fRadius);

	pVB->Unlock();
	SAFE_RELEASE(pVB);

	

//	pMesh->m_Sphere->Center = vCenter;
	pMesh->m_Sphere.Radius = fRadius*0.7;//���̂܂܂ł́A���܂�ɂ����ʂ�����̂ŏk��

										 //����ȍ~�̍s�͖{���͕s�v�B�m�F�̂��߃X�t�B�A���̂������_�����O���邽�߂̂���

										 // ����ꂽ���S�Ɣ��a����ɉ����p���b�V���Ƃ��ẴX�t�B�A���쐬����
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
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pMeshB->m_Pos - pMeshA->m_Pos;
	float Length = D3DXVec3Length(&vLength);
	//2���̊Ԃ̋������A2���̂̔��a�𑫂������̂�菬�����Ƃ������Ƃ́A
	//���E�����m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������
	if (Length <= pMeshA->m_Sphere.Radius + pMeshB->m_Sphere.Radius)
	{
		return true;
	}
	return false;
}
