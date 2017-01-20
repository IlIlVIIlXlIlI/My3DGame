#pragma once
#include "BASE.h"
#include "WINDOW.h"
#include "DIRECT3D11.h"
#include "Player.h"
#include "CD3DXMESH.h"
//
//
//
class CAMERA : public CELEMENT
{
private:
	//=======================================================================================
	//Method
	//=======================================================================================
	HRESULT SetViewProj();

public:
	//=======================================================================================
	//Data
	//=======================================================================================

	/*カメラの位置ステータス*/
	enum Camera_Status
	{
		PLAYER_BACK,		//プレイヤーの背後

		PLAYER_SQUAD,		//しゃがんだ時

		PLAYER_BOW,			//弓を構えた時のプレイヤーの背後	

		WALL_FRONT,			//壁の横歩き

		GETTING_UP			//立ち上がる
	};

	Camera_Status m_CamStatus = PLAYER_BACK;

	DIRECT3D11* m_pD3D;

	float m_fX;
	float m_fY;
	float m_fZ;
	float m_fGX;//注視
	float m_fGY;//注視
	float m_fGZ;//注視
	DWORD m_dwWindowWidth;
	DWORD m_dwWindowHeight;
	bool m_boGaze;//=true 注視ありモード
	D3DXVECTOR3 m_vPos;
	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;
	D3DXVECTOR3 CLook;
	D3DXVECTOR3 mCPos;
	LPD3DXMESH m_pD3DXMesh;
	float m_Radius;
	//=======================================================================================
	//Method
	//=======================================================================================
	CAMERA(const int _WINDOW_WIDTH, const int _WINDOW_HEIGHT);
	void SetCameraPosition(float x,float y,float z);
	void SetCameraPositionGaze(float x,float y,float z,float gx,float gy,float gz);//注視あり
	HRESULT Init(DWORD dwWidth,DWORD dwHeight);
	

	/*更新*/
	void Update();

	//void GetPlayerPosition(D3DXVECTOR3 _Position);

	D3DXVECTOR3 GetRayDistance(CD3DXMESH* _pMesh, D3DXVECTOR3& RayStart, D3DXVECTOR3 RayEnd);
};