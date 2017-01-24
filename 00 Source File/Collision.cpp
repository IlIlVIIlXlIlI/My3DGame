#include "Collision.h"

bool COLLISION::RayIntersect(ChrBase* pMeshA, CD3DXMESH* pMeshB, float* pfDistance, DWORD* pdwIndex)
{
	float fDistance = 0;
	DWORD dwIndex = 0;
	BOOL boHit = false;

	D3DXMATRIX mWorld, mRotation;
	D3DXVECTOR3 vStart, vEnd, vDirection;
	//レイを出すメッシュの位置・回転をレイに適用
	vStart = pMeshA->m_Pos;
	vEnd = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixRotationY(&mRotation, pMeshA->m_Yaw);
	D3DXVec3TransformCoord(&vEnd, &vEnd, &mRotation);
	vEnd += vStart;
	//レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMatrixTranslation(&mWorld, pMeshB->m_Pos.x, pMeshB->m_Pos.y, pMeshB->m_Pos.z);
	D3DXMatrixInverse(&mWorld, nullptr, &mWorld);
	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);
	D3DXVec3TransformCoord(&vEnd, &vEnd, &mWorld);

	vDirection = vEnd - vStart;
	D3DXIntersect(pMeshB->m_pMesh, &vStart, &vDirection, &boHit, pdwIndex, 0, 0, pfDistance, 0, 0);
	if (boHit)
	{
		return true;
	}
	return false;
}

float COLLISION::RayIntersectDown(ChrBase* pMeshA, CD3DXMESH* pMeshB, float* pfDistance)
{
	float fDistance = 0;
	DWORD dwIndex = 0;
	BOOL boHit = false;

	
	D3DXVECTOR3 vPos, vDir;
	//レイを出すメッシュの位置・回転をレイに適用
	vPos = pMeshA->m_Pos;
	vPos.y += 1.0f;
	vDir = D3DXVECTOR3(0, -1, 0);
	//レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMATRIX mInv;
	D3DXMATRIX mWorld;
	mWorld = pMeshB->GetWorld();
	D3DXMatrixInverse(&mInv, NULL, &mWorld);
	D3DXVECTOR3 lPos, lVec;
	D3DXVec3TransformCoord(&lPos, &vPos, &mWorld);
	D3DXVec3TransformNormal(&lVec, &vDir, &mWorld);

	D3DXIntersect(pMeshB->m_pMesh, &lPos, &lVec, &boHit, 0, 0, 0, pfDistance, 0, 0);
	if (boHit)
	{
		return *pfDistance;
	}
	return -1.0f;
}


float COLLISION::RayGetDistance(HWND m_hWnd,ChrBase* _pMeshA, CD3DXMESH* _pMeshB)
{

	float fDistance = 999;
	DWORD dwIndex = 0;
	BOOL boHit = false;
	if (RayIntersect(_pMeshA, _pMeshB, &fDistance, &dwIndex) && fDistance <= RAY_DISTANCE)
	{
		char Str[MAX_PATH + 1];
		//sprintf(Str, "レイが相手メッシュと交差しています。距離 : %3.2f 交差しているポリゴンの番号は%d", fDistance, dwIndex);
		//SetWindowTextA(m_hWnd, Str);
	}
	else
	{
		//SetWindowTextA(m_hWnd, "交差無し");
	}

	if (fDistance <= 1.5f)
	{
		char Str[MAX_PATH + 1];
		//	assert((fDistance <= 1.5f) && "XXX:不正な数値です");
		//sprintf(Str, "レイが相手メッシュと交差しています。距離 : %3.2f 交差しているポリゴンの番号は%d", fDistance, dwIndex);
		//SetWindowTextA(m_hWnd, Str);
		//m_pPlayer->m_Pos = D3DXVECTOR3(0, 0, 0);
	}

	return fDistance;
}


