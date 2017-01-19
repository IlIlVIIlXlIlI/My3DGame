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
	// ビュー
	if(!m_boGaze)
	{
		D3DXVECTOR3 vEyePt( m_fX, m_fY,m_fZ );		//カメラ（視点）位置
		D3DXVECTOR3 vLookatPt( m_fX, m_fY,m_fZ+1 );	//注視位置
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );		//上方位置
	
		D3DXMatrixLookAtLH( &m_mView, &vEyePt, &vLookatPt, &vUpVec );
	}
	else
	{
		D3DXVECTOR3 vEyePt( m_fX, m_fY,m_fZ );		//カメラ（視点）位置
		D3DXVECTOR3 vLookatPt( m_fGX, m_fGY,m_fGZ );//注視位置
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );		//上方位置
		
		D3DXMatrixLookAtLH( &m_mView, &vEyePt, &vLookatPt, &vUpVec );
	}
	m_boGaze=false;
	// プロジェクション

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
	///TODO : Stateパターンを活用する
	switch (m_CamStatus)
	{
	case PLAYER_BACK:
		mCPos = D3DXVECTOR3(0.0f, 2.0f, -5.5f);//カメラ座標
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
		assert((m_CamStatus >= 0 && m_CamStatus <= m_CamStatus == WALL_FRONT) && "XXX: 不正な数値があります");
		break;
	}

	/*操作されていない時は常にプレイヤーの背後に*/
	m_CamStatus = PLAYER_BACK;
}

//void CAMERA::Update(Player* _player)
//{
//	//メッシュ　表示
//	D3DXMATRIX mView, mProj;
//
//	D3DXVECTOR3 mCPos = D3DXVECTOR3(0.0f, 2.0f, -4.0f);//カメラ座標
//	D3DXVec3TransformCoord(&mCPos, &mCPos, &_player->mCRot);
//
//	D3DXMatrixTranslation(&_player->mTrans, _player->m_Pos.x, _player->m_Pos.y, _player->m_Pos.z);
//
//	mCPos.x += _player->mTrans._41;
//	mCPos.y += _player->mTrans._42;
//	mCPos.z += _player->mTrans._43;
//
//
//	CLook = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//注視点設定
//	D3DXVec3TransformCoord(&CLook, &CLook, &_player->mTrans);
//	D3DXVECTOR3 CHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//頭上方向設定
//
//
//
//	D3DXMatrixLookAtLH(&mView, &mCPos, &CLook, &CHead);  //視点行列の設定
//
//														 // プロジェクショントランスフォーム（射影変換）
//	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
//}

//何もなければ、RayEndの位置を返す
D3DXVECTOR3 CAMERA::GetRayDistance(CD3DXMESH* _pMesh, D3DXVECTOR3& RayStart, D3DXVECTOR3 RayEnd)
{
	//メッシュが複数あるときは、もちろん全てのメッシュ（カメラとキャラの間に入る可能性のあるメッシュ）と
	//レイ判定することになる 今回はsky_cityメッシュしかないので、sky_cityメッシュのみ判定

	BOOL Hit = false;
	float Dist = 0xffffffff;
	int face = _pMesh->m_pMesh->GetNumFaces();
	D3DXVECTOR3 Dir = RayEnd - RayStart;
	D3DXVec3Normalize(&Dir, &Dir);
	D3DXIntersect(_pMesh->m_pMesh, &RayStart, &Dir, &Hit, NULL, NULL, NULL, &Dist, NULL, NULL);

	float RayLength = D3DXVec3Length(&(RayEnd - RayStart));
	if (Dist< RayLength)//スタートとエンドの間にポリゴン（視界を遮蔽するもの）がある場合
	{
		return RayStart + Dir*Dist*0.9;
	}
	return RayEnd;

}