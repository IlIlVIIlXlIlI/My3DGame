#include "Frustum.h"

//視界内：true 外：false 
bool Frustum::VFCulling(CD3DXMESH* _pMesh, D3DXMATRIX* _pmView, float _Angle, float _NearClip, float _FarClip, float _Aspect)
{
	D3DXPLANE VFLeftPlane, VFRightPlane, VFTopPlane, VFBottomPlane;
	D3DXVECTOR3 Pos = _pMesh->m_Pos;
	float Radius = _pMesh->m_Radius;
	//まず、ジオメトリの位置ベクトルをワールドからビュー空間に変換
	D3DXVec3TransformCoord(&Pos, &Pos, _pmView);

	//左右、上下の平面を計算
	{
		D3DXVECTOR3 p1, p2, p3;
		//左面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
		//右面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
		//上面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
		//下面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
	}

	//6つの平面とジオメトリ境界球をチェック
	{
		//ニアクリップ面について
		if ((Pos.z + Radius) < _NearClip)
		{
			return false;
		}
		//ファークリップ面について
		if ((Pos.z - Radius) > _FarClip)
		{
			return false;
		}
		//左クリップ面について
		float Distance = (Pos.x * VFLeftPlane.a) + (Pos.z * VFLeftPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//右クリップ面について
		Distance = (Pos.x * VFRightPlane.a) + (Pos.z * VFRightPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//上クリップ面について
		Distance = (Pos.y * VFTopPlane.b) + (Pos.z * VFTopPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//下クリップ面について
		Distance = (Pos.y * VFBottomPlane.b) + (Pos.z * VFBottomPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
	}

	return true;
}

//視界内：true 外：false 
bool Frustum::VFCulling(CD3DXSKINMESH* _pMesh, D3DXMATRIX* _pmView, float _Angle, float _NearClip, float _FarClip, float _Aspect)
{
	D3DXPLANE VFLeftPlane, VFRightPlane, VFTopPlane, VFBottomPlane;
	D3DXVECTOR3 Pos = _pMesh->m_Pos;
	float Radius = _pMesh->m_Radius;
	//まず、ジオメトリの位置ベクトルをワールドからビュー空間に変換
	D3DXVec3TransformCoord(&Pos, &Pos, _pmView);

	//左右、上下の平面を計算
	{
		D3DXVECTOR3 p1, p2, p3;
		//左面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
		//右面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
		//上面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
		//下面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
	}

	//6つの平面とジオメトリ境界球をチェック
	{
		//ニアクリップ面について
		if ((Pos.z + Radius) < _NearClip)
		{
			return false;
		}
		//ファークリップ面について
		if ((Pos.z - Radius) > _FarClip)
		{
			return false;
		}
		//左クリップ面について
		float Distance = (Pos.x * VFLeftPlane.a) + (Pos.z * VFLeftPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//右クリップ面について
		Distance = (Pos.x * VFRightPlane.a) + (Pos.z * VFRightPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//上クリップ面について
		Distance = (Pos.y * VFTopPlane.b) + (Pos.z * VFTopPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//下クリップ面について
		Distance = (Pos.y * VFBottomPlane.b) + (Pos.z * VFBottomPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
	}

	return true;
}

//視界内：true 外：false 
bool Frustum::VFCulling(CAMERA* _pMesh, D3DXMATRIX* _pmView, float _Angle, float _NearClip, float _FarClip, float _Aspect)
{
	D3DXPLANE VFLeftPlane, VFRightPlane, VFTopPlane, VFBottomPlane;
	D3DXVECTOR3 Pos = _pMesh->m_vPos;
	float Radius = _pMesh->m_Radius;
	//まず、ジオメトリの位置ベクトルをワールドからビュー空間に変換
	D3DXVec3TransformCoord(&Pos, &Pos, _pmView);

	//左右、上下の平面を計算
	{
		D3DXVECTOR3 p1, p2, p3;
		//左面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
		//右面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
		//上面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
		//下面
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
	}

	//6つの平面とジオメトリ境界球をチェック
	{
		//ニアクリップ面について
		if ((Pos.z + Radius) < _NearClip)
		{
			return false;
		}
		//ファークリップ面について
		if ((Pos.z - Radius) > _FarClip)
		{
			return false;
		}
		//左クリップ面について
		float Distance = (Pos.x * VFLeftPlane.a) + (Pos.z * VFLeftPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//右クリップ面について
		Distance = (Pos.x * VFRightPlane.a) + (Pos.z * VFRightPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//上クリップ面について
		Distance = (Pos.y * VFTopPlane.b) + (Pos.z * VFTopPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//下クリップ面について
		Distance = (Pos.y * VFBottomPlane.b) + (Pos.z * VFBottomPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
	}

	return true;
}