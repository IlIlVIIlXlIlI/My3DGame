#include "Frustum.h"

//���E���Ftrue �O�Ffalse 
bool Frustum::VFCulling(CD3DXMESH* _pMesh, D3DXMATRIX* _pmView, float _Angle, float _NearClip, float _FarClip, float _Aspect)
{
	D3DXPLANE VFLeftPlane, VFRightPlane, VFTopPlane, VFBottomPlane;
	D3DXVECTOR3 Pos = _pMesh->m_Pos;
	float Radius = _pMesh->m_Radius;
	//�܂��A�W�I���g���̈ʒu�x�N�g�������[���h����r���[��Ԃɕϊ�
	D3DXVec3TransformCoord(&Pos, &Pos, _pmView);

	//���E�A�㉺�̕��ʂ��v�Z
	{
		D3DXVECTOR3 p1, p2, p3;
		//����
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
		//�E��
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
		//���
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
		//����
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
	}

	//6�̕��ʂƃW�I���g�����E�����`�F�b�N
	{
		//�j�A�N���b�v�ʂɂ���
		if ((Pos.z + Radius) < _NearClip)
		{
			return false;
		}
		//�t�@�[�N���b�v�ʂɂ���
		if ((Pos.z - Radius) > _FarClip)
		{
			return false;
		}
		//���N���b�v�ʂɂ���
		float Distance = (Pos.x * VFLeftPlane.a) + (Pos.z * VFLeftPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//�E�N���b�v�ʂɂ���
		Distance = (Pos.x * VFRightPlane.a) + (Pos.z * VFRightPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//��N���b�v�ʂɂ���
		Distance = (Pos.y * VFTopPlane.b) + (Pos.z * VFTopPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//���N���b�v�ʂɂ���
		Distance = (Pos.y * VFBottomPlane.b) + (Pos.z * VFBottomPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
	}

	return true;
}

//���E���Ftrue �O�Ffalse 
bool Frustum::VFCulling(CD3DXSKINMESH* _pMesh, D3DXMATRIX* _pmView, float _Angle, float _NearClip, float _FarClip, float _Aspect)
{
	D3DXPLANE VFLeftPlane, VFRightPlane, VFTopPlane, VFBottomPlane;
	D3DXVECTOR3 Pos = _pMesh->m_Pos;
	float Radius = _pMesh->m_Radius;
	//�܂��A�W�I���g���̈ʒu�x�N�g�������[���h����r���[��Ԃɕϊ�
	D3DXVec3TransformCoord(&Pos, &Pos, _pmView);

	//���E�A�㉺�̕��ʂ��v�Z
	{
		D3DXVECTOR3 p1, p2, p3;
		//����
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
		//�E��
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
		//���
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
		//����
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
	}

	//6�̕��ʂƃW�I���g�����E�����`�F�b�N
	{
		//�j�A�N���b�v�ʂɂ���
		if ((Pos.z + Radius) < _NearClip)
		{
			return false;
		}
		//�t�@�[�N���b�v�ʂɂ���
		if ((Pos.z - Radius) > _FarClip)
		{
			return false;
		}
		//���N���b�v�ʂɂ���
		float Distance = (Pos.x * VFLeftPlane.a) + (Pos.z * VFLeftPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//�E�N���b�v�ʂɂ���
		Distance = (Pos.x * VFRightPlane.a) + (Pos.z * VFRightPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//��N���b�v�ʂɂ���
		Distance = (Pos.y * VFTopPlane.b) + (Pos.z * VFTopPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//���N���b�v�ʂɂ���
		Distance = (Pos.y * VFBottomPlane.b) + (Pos.z * VFBottomPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
	}

	return true;
}

//���E���Ftrue �O�Ffalse 
bool Frustum::VFCulling(CAMERA* _pMesh, D3DXMATRIX* _pmView, float _Angle, float _NearClip, float _FarClip, float _Aspect)
{
	D3DXPLANE VFLeftPlane, VFRightPlane, VFTopPlane, VFBottomPlane;
	D3DXVECTOR3 Pos = _pMesh->m_vPos;
	float Radius = _pMesh->m_Radius;
	//�܂��A�W�I���g���̈ʒu�x�N�g�������[���h����r���[��Ԃɕϊ�
	D3DXVec3TransformCoord(&Pos, &Pos, _pmView);

	//���E�A�㉺�̕��ʂ��v�Z
	{
		D3DXVECTOR3 p1, p2, p3;
		//����
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFLeftPlane, &p1, &p2, &p3);
		//�E��
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = p2.x;
		p3.y = -p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFRightPlane, &p1, &p2, &p3);
		//���
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = -_FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = _FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFTopPlane, &p1, &p2, &p3);
		//����
		p1 = D3DXVECTOR3(0, 0, 0);
		p2.x = _FarClip * ((FLOAT)tan(_Angle / 2)*_Aspect);
		p2.y = -_FarClip * (FLOAT)tan(_Angle / 2);
		p2.z = _FarClip;
		p3.x = -p2.x;
		p3.y = p2.y;
		p3.z = p2.z;
		D3DXPlaneFromPoints(&VFBottomPlane, &p1, &p2, &p3);
	}

	//6�̕��ʂƃW�I���g�����E�����`�F�b�N
	{
		//�j�A�N���b�v�ʂɂ���
		if ((Pos.z + Radius) < _NearClip)
		{
			return false;
		}
		//�t�@�[�N���b�v�ʂɂ���
		if ((Pos.z - Radius) > _FarClip)
		{
			return false;
		}
		//���N���b�v�ʂɂ���
		float Distance = (Pos.x * VFLeftPlane.a) + (Pos.z * VFLeftPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//�E�N���b�v�ʂɂ���
		Distance = (Pos.x * VFRightPlane.a) + (Pos.z * VFRightPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//��N���b�v�ʂɂ���
		Distance = (Pos.y * VFTopPlane.b) + (Pos.z * VFTopPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
		//���N���b�v�ʂɂ���
		Distance = (Pos.y * VFBottomPlane.b) + (Pos.z * VFBottomPlane.c);
		if (Distance>Radius)
		{
			return false;
		}
	}

	return true;
}