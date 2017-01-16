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
	//対象メッシュのポリゴン全てを総当りで調べる。それぞれのポリゴンを平面方程式にして、レイと判定
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVECTOR3 vNormal(0, 0, 0);
	bool ret = false;
	float MinLength = FLT_MAX;

	D3DXVECTOR3 vEnd = vStart + vDir * 50;//レイの長さとりあえず50単位

	D3DXPLANE plane;
	for (DWORD i = 0; i<TargetMesh->m_dwNumMaterial; i++)
	{
		for (DWORD k = 0; k<TargetMesh->dwNumFaceInMaterial[i]; k++)
		{
			//このポリゴンの3点を取得
			D3DXVECTOR3 v1, v2, v3;
			int index1 = TargetMesh->ppiVertexIndex[i][k * 3 + 0];
			int index2 = TargetMesh->ppiVertexIndex[i][k * 3 + 1];
			int index3 = TargetMesh->ppiVertexIndex[i][k * 3 + 2];

			v1 = TargetMesh->pvVertexBuffer[index1].vPos;
			v2 = TargetMesh->pvVertexBuffer[index2].vPos;
			v3 = TargetMesh->pvVertexBuffer[index3].vPos;
			//3点から平面方程式を作る
			CalcPlane(&plane, &v1, &v2, &v3);
			//平面とレイの交差を検出
			if (Intersect(plane, vStart, vEnd, v1, v2, v3, fLength))
			{
				ret = true;
				if (MinLength>*fLength)
				{
					vNormal.x = plane.a;//平面方程式の係数は面法線
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