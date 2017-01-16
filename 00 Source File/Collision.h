#pragma once
#include "BASE.h"
#include "CharacterBase.h"
#include "CD3DXMESH.h"


class COLLISION
{
private:

	//クローンの頂点バッファ
	struct CLONE_VERTEX
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Nomal;
		D3DXVECTOR2 Tex;
	};

	

public:
   
	//=============================================================
	//地形との距離を測る用のレイ
	//=============================================================
	bool RayIntersect(ChrBase*, CD3DXMESH*, float*, DWORD*);
	float RayGetDistance(HWND m_hWnd,ChrBase* _pMeshA, CD3DXMESH* _pMeshB);

	//void MeshColl(D3DXVECTOR3 *_Pos, D3DXVECTOR3 *_Vec, D3DXMATRIX *_World, float _Dis);
	//メッシュレイ判定 　第１引数のメッシュは、あたり判定に使用するメッシュ
	//BOOL Intersect(CD3DXMESH _mesh, D3DXVECTOR3 &_pos, D3DXVECTOR3 &_vec, D3DXMATRIX &_world, float &_dis, DWORD *_PolyNo = NULL, DWORD *_HitCnt = NULL);

	/*下向き用のレイ*/
	float RayIntersectDown(ChrBase* pMeshA, CD3DXMESH* pMeshB, float* pfDistance);
};