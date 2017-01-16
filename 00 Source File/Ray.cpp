#include "Ray.h"


HRESULT	Ray::Init(ID3D11DeviceContext*)
{

}
HRESULT	Ray::MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**)
{

}
void Ray::RenderMesh(MY_MESH* pMesh)
{

}
void Ray::DestroyD3D()
{

}

bool Ray::RayHitDetection(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, MY_MESH* TargetMesh, float* fLength, D3DXVECTOR3* pvNormal)
{
	//�Ώۃ��b�V���̃|���S���S�Ă𑍓���Œ��ׂ�B���ꂼ��̃|���S���𕽖ʕ������ɂ��āA���C�Ɣ���
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVECTOR3 vNormal(0, 0, 0);
	bool ret = false;
	float MinLength = FLT_MAX;

	D3DXVECTOR3 vEnd = vStart + vDir * 50;//���C�̒����Ƃ肠����50�P��

	D3DXPLANE plane;
	for (DWORD i = 0; i<TargetMesh->m_dwNumMaterial; i++)
	{
		for (DWORD k = 0; k<TargetMesh->dwNumFaceInMaterial[i]; k++)
		{
			//���̃|���S����3�_���擾
			D3DXVECTOR3 v1, v2, v3;
			int index1 = TargetMesh->ppiVertexIndex[i][k * 3 + 0];
			int index2 = TargetMesh->ppiVertexIndex[i][k * 3 + 1];
			int index3 = TargetMesh->ppiVertexIndex[i][k * 3 + 2];

			v1 = TargetMesh->pvVertexBuffer[index1].vPos;
			v2 = TargetMesh->pvVertexBuffer[index2].vPos;
			v3 = TargetMesh->pvVertexBuffer[index3].vPos;
			//3�_���畽�ʕ����������
			CalcPlane(&plane, &v1, &v2, &v3);
			//���ʂƃ��C�̌��������o
			if (Intersect(plane, vStart, vEnd, v1, v2, v3, fLength))
			{
				ret = true;
				if (MinLength>*fLength)
				{
					vNormal.x = plane.a;//���ʕ������̌W���͖ʖ@��
					vNormal.y = plane.b;
					vNormal.z = plane.c;
					MinLength = *fLength;
				}
			}
		}
	}

	*pvNormal = vNormal;
	*fLength = MinLength;
	return ret;
}

void Ray::CalcPlane(D3DXPLANE* pPlane, D3DXVECTOR3* pvA, D3DXVECTOR3* pvB, D3DXVECTOR3* pvC)
{

}
void Ray::sInside(D3DXVECTOR3* pvI, D3DXVECTOR3* pvA, D3DXVECTOR3* pvB, D3DXVECTOR3* pvC)
{

}
bool Ray::Intersect(D3DXPLANE p, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, float* pfLen)
{
	
}
D3DXVECTOR3 Ray::Slip(D3DXVECTOR3 l, D3DXVECTOR3 n)
{

}


HRESULT Ray::InitStaticMesh(LPSTR FileName, MY_MESH* pMesh)
{

}
HRESULT Ray:LoadMaterialFromFile(LPSTR FileName, MY_MATERIAL** ppMaterial, DWORD* pdwNUmMaterial)
{

}