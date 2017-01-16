#pragma once
#include "BASE.h"
#include "CharacterBase.h"
#include "CD3DXMESH.h"


class COLLISION
{
private:

	//�N���[���̒��_�o�b�t�@
	struct CLONE_VERTEX
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Nomal;
		D3DXVECTOR2 Tex;
	};

	

public:
   
	//=============================================================
	//�n�`�Ƃ̋����𑪂�p�̃��C
	//=============================================================
	bool RayIntersect(ChrBase*, CD3DXMESH*, float*, DWORD*);
	float RayGetDistance(HWND m_hWnd,ChrBase* _pMeshA, CD3DXMESH* _pMeshB);

	//void MeshColl(D3DXVECTOR3 *_Pos, D3DXVECTOR3 *_Vec, D3DXMATRIX *_World, float _Dis);
	//���b�V�����C���� �@��P�����̃��b�V���́A�����蔻��Ɏg�p���郁�b�V��
	//BOOL Intersect(CD3DXMESH _mesh, D3DXVECTOR3 &_pos, D3DXVECTOR3 &_vec, D3DXMATRIX &_world, float &_dis, DWORD *_PolyNo = NULL, DWORD *_HitCnt = NULL);

	/*�������p�̃��C*/
	float RayIntersectDown(ChrBase* pMeshA, CD3DXMESH* pMeshB, float* pfDistance);
};