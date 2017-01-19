#include "CAMERA.h"

//
//
//
CAMERA::CAMERA(const int _WINDOW_WIDTH,const int _WINDOW_HEIGHT)
{
	//ZeroMemory(this,sizeof(CAMERA));
	Init(_WINDOW_WIDTH, _WINDOW_HEIGHT);
}

//
//
//
//
//
//
void CAMERA::SetCameraPosition(float _x,float _y,float _z)
{
	m_fX=_x;
	m_fY=_y;
	m_fZ=_z;
	m_vPos=D3DXVECTOR3(_x,_y,_z);
	SetViewProj();
}
//
//
//
void CAMERA::SetCameraPositionGaze(float _x,float _y,float _z,float _gx,float _gy,float _gz)
{
	m_fX=_x;
	m_fY=_y;
	m_fZ=_z;
	m_vPos=D3DXVECTOR3(_x,_y,_z);
	m_fGX=_gx;
	m_fGY=_gy;
	m_fGZ=_gz;

	m_boGaze=true;
	SetViewProj();
}
//
//
//
HRESULT CAMERA::SetViewProj()
{
	// �r���[
	if(!m_boGaze)
	{
		D3DXVECTOR3 vEyePt( m_fX, m_fY,m_fZ );		//�J�����i���_�j�ʒu
		D3DXVECTOR3 vLookatPt( m_fX, m_fY,m_fZ+1 );	//�����ʒu
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );		//����ʒu
	
		D3DXMatrixLookAtLH( &m_mView, &vEyePt, &vLookatPt, &vUpVec );
	}
	else
	{
		D3DXVECTOR3 vEyePt( m_fX, m_fY,m_fZ );		//�J�����i���_�j�ʒu
		D3DXVECTOR3 vLookatPt( m_fGX, m_fGY,m_fGZ );//�����ʒu
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );		//����ʒu
		
		D3DXMatrixLookAtLH( &m_mView, &vEyePt, &vLookatPt, &vUpVec );
	}
	m_boGaze=false;
	// �v���W�F�N�V����

	D3DXMatrixPerspectiveFovLH( &m_mProj, D3DX_PI/4, (FLOAT)m_dwWindowWidth/(FLOAT)m_dwWindowHeight, 0.1f, 1100.0f );

	return S_OK;
}
//
//
//
HRESULT CAMERA::Init(DWORD _dwWidth,DWORD _dwHeight)
{
	m_dwWindowWidth= _dwWidth;
	m_dwWindowHeight=_dwHeight;
	return S_OK;
}

void CAMERA::Update()
{
	///TODO : State�p�^�[�������p����
	switch (m_CamStatus)
	{
	case PLAYER_BACK:
		mCPos = D3DXVECTOR3(0.0f, 2.0f, -5.5f);//�J�������W
		break;
	case PLAYER_SQUAD:
		mCPos = D3DXVECTOR3(0.0f, 1.0f, -2.0f);
		break;
	case PLAYER_BOW:
		mCPos = D3DXVECTOR3(0.0f, 1.7f, -0.6f);
		CLook = D3DXVECTOR3(0.0f, 1.0f, 1.5f);
	case WALL_FRONT:
		break;
	default:
		assert((m_CamStatus >= 0 && m_CamStatus <= m_CamStatus == WALL_FRONT) && "XXX: �s���Ȑ��l������܂�");
		break;
	}

	/*���삳��Ă��Ȃ����͏�Ƀv���C���[�̔w���*/
	m_CamStatus = PLAYER_BACK;
}

//void CAMERA::Update(Player* _player)
//{
//	//���b�V���@�\��
//	D3DXMATRIX mView, mProj;
//
//	D3DXVECTOR3 mCPos = D3DXVECTOR3(0.0f, 2.0f, -4.0f);//�J�������W
//	D3DXVec3TransformCoord(&mCPos, &mCPos, &_player->mCRot);
//
//	D3DXMatrixTranslation(&_player->mTrans, _player->m_Pos.x, _player->m_Pos.y, _player->m_Pos.z);
//
//	mCPos.x += _player->mTrans._41;
//	mCPos.y += _player->mTrans._42;
//	mCPos.z += _player->mTrans._43;
//
//
//	CLook = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�����_�ݒ�
//	D3DXVec3TransformCoord(&CLook, &CLook, &_player->mTrans);
//	D3DXVECTOR3 CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//��������ݒ�
//
//
//
//	D3DXMatrixLookAtLH(&mView, &mCPos, &CLook, &CHead);  //���_�s��̐ݒ�
//
//														 // �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
//	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
//}

//�����Ȃ���΁ARayEnd�̈ʒu��Ԃ�
D3DXVECTOR3 CAMERA::GetRayDistance(CD3DXMESH* _pMesh, D3DXVECTOR3& RayStart, D3DXVECTOR3 RayEnd)
{
	//���b�V������������Ƃ��́A�������S�Ẵ��b�V���i�J�����ƃL�����̊Ԃɓ���\���̂��郁�b�V���j��
	//���C���肷�邱�ƂɂȂ� �����sky_city���b�V�������Ȃ��̂ŁAsky_city���b�V���̂ݔ���

	BOOL Hit = false;
	float Dist = 0xffffffff;
	int face = _pMesh->m_pMesh->GetNumFaces();
	D3DXVECTOR3 Dir = RayEnd - RayStart;
	D3DXVec3Normalize(&Dir, &Dir);
	D3DXIntersect(_pMesh->m_pMesh, &RayStart, &Dir, &Hit, NULL, NULL, NULL, &Dist, NULL, NULL);

	float RayLength = D3DXVec3Length(&(RayEnd - RayStart));
	if (Dist< RayLength)//�X�^�[�g�ƃG���h�̊ԂɃ|���S���i���E���Օ�������́j������ꍇ
	{
		return RayStart + Dir*Dist*0.9;
	}
	return RayEnd;

}