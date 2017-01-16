#include <stdlib.h>
#include "CD3DXSKINMESH.h"

#pragma comment(linker, "/HEAP:5242880")
#pragma comment(linker, "/STACK:5242880")

std::vector<DWORD *>D3DXPARSER::BoneList;
std::vector<float *>D3DXPARSER::ABList;


const float HlAnimation_Desc::m_CShiftTime = 0.0f;


HlAnimation_Desc::HlAnimation_Desc()
{

}

HlAnimation_Desc::~HlAnimation_Desc()
{

}


//======================================================================================
//HRESULT MY_HIERARCHY::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame)
//�t���[�����쐬����
//======================================================================================
HRESULT MY_HIERARCHY::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	HRESULT hr = S_OK;
	MYFRAME *pFrame;

	*ppNewFrame = nullptr;

	pFrame = new MYFRAME;
	if (pFrame == nullptr)
	{
		return E_OUTOFMEMORY;
	}
	pFrame->Name=new CHAR[strlen(Name) + 1];
	if (!pFrame->Name)
	{
		return E_FAIL;
	}
	strcpy(pFrame->Name,Name);

	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

	*ppNewFrame = pFrame;

	return S_OK;
}

//======================================================================================
//HRESULT MY_HIERARCHY::CreateMeshContainer
//���b�V���R���e�i�[���쐬����
//======================================================================================
HRESULT MY_HIERARCHY::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData,
							CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances,
							DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
							LPD3DXMESHCONTAINER *ppMeshContainer)
{
	*ppMeshContainer = nullptr;
	DWORD dwBoneNum=0;

	MYMESHCONTAINER *pMeshContainer = new MYMESHCONTAINER;
	ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));
	pMeshContainer->Name=new CHAR[strlen(Name) + 1];
	strcpy(pMeshContainer->Name,Name);	

	memcpy(&pMeshContainer->MeshData,pMeshData,sizeof(pMeshContainer->MeshData));
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	int NumPoly=pMeshContainer->MeshData.pMesh->GetNumFaces();
	//���b�V���𕡐�����B�@�Ȃ����X�L�����b�V�����ƁA���̊֐��𔲂��������D3DX�����Ń��b�V���|�C���^�[�����������Ȃ��Ă��܂��̂ŁB
	LPDIRECT3DDEVICE9 pDevice=nullptr;
	pMeshContainer->MeshData.pMesh->GetDevice(&pDevice);
	LPD3DXMESH pMesh=nullptr;
	pMeshContainer->MeshData.pMesh->CloneMesh(D3DXMESH_32BIT,nullptr,pDevice,&pMesh);
	//SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	pMeshContainer->MeshData.pMesh=pMesh;

	//���b�V���̃}�e���A���ݒ�
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[pMeshContainer->MeshData.pMesh->GetNumFaces()*3];
	if ((pMeshContainer->pAdjacency == nullptr) || (pMeshContainer->pMaterials == nullptr))
	{
		return E_FAIL;
	}
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumPoly*3);

	if (NumMaterials > 0)
	{
		for(int i=0;i<NumMaterials;i++)
		{			
			memcpy(&pMeshContainer->pMaterials[i], &pMaterials[i], sizeof(D3DXMATERIAL) );
			if (pMaterials[i].pTextureFilename != nullptr)
			{
				pMeshContainer->pMaterials[i].pTextureFilename=new CHAR[512];
				strcpy(pMeshContainer->pMaterials[i].pTextureFilename,pMaterials[i].pTextureFilename);
			}
		}
	}
	else
	{
		pMeshContainer->pMaterials[0].pTextureFilename = nullptr;
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}
	//���Y���b�V�����X�L�����������Ă���ꍇ�i�X�L�����b�V���ŗL�̏����j
	if (pSkinInfo != nullptr)
	{
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();
		dwBoneNum = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[dwBoneNum];

		for (DWORD i= 0; i < dwBoneNum; i++)
		{	
			memcpy(&pMeshContainer->pBoneOffsetMatrices[i],
				pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i),sizeof(D3DMATRIX));
		}
	}
	//���[�J���ɐ����������b�V���R���e�i�[���Ăяo�����ɃR�s�[����
	*ppMeshContainer = pMeshContainer;

	return S_OK;
}

//======================================================================================
//HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
//�t���[����j������
//======================================================================================
HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
{
    SAFE_DELETE_ARRAY( pFrameToFree->Name );

	if(pFrameToFree->pFrameFirstChild)
	{
		DestroyFrame(pFrameToFree->pFrameFirstChild);
	}
	if(pFrameToFree->pFrameSibling)
	{
		DestroyFrame(pFrameToFree->pFrameSibling);
	}

	SAFE_DELETE( pFrameToFree );

    return S_OK; 
}

//======================================================================================
//HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
//���b�V���R���e�i�[��j������
//======================================================================================
HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	int iMaterial;
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;

	SAFE_DELETE_ARRAY( pMeshContainer->Name );
	SAFE_RELEASE(pMeshContainer->pSkinInfo);
	SAFE_DELETE_ARRAY( pMeshContainer->pAdjacency );
	SAFE_DELETE_ARRAY( pMeshContainer->pMaterials );

	SAFE_DELETE_ARRAY( pMeshContainer->ppBoneMatrix );

	if (pMeshContainer->ppTextures != nullptr)
	{
		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			SAFE_RELEASE( pMeshContainer->ppTextures[iMaterial] );
		}
	}
	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);

	SAFE_RELEASE( pMeshContainer->MeshData.pMesh );

	if(pMeshContainer->pBoneBuffer != nullptr)
	{
		SAFE_RELEASE( pMeshContainer->pBoneBuffer );
		SAFE_DELETE_ARRAY( pMeshContainer->pBoneOffsetMatrices );
	}

	SAFE_DELETE( pMeshContainer );

	return S_OK;
}

//======================================================================================
//
//======================================================================================
HRESULT D3DXPARSER::AllocateBoneMatrix( LPD3DXMESHCONTAINER pMeshContainerBase )
{
	MYFRAME *pFrame=nullptr;
	DWORD dwBoneNum=0;

	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == nullptr)
	{
		return S_OK;
	}
	dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[dwBoneNum];

	for (DWORD i=0; i<dwBoneNum; i++)
	{
		pFrame = (MYFRAME*)D3DXFrameFind( m_pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i) );
		if (pFrame == nullptr)
		{
			return E_FAIL;
		}
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;

	}
	return S_OK;
}
//
//
//
HRESULT D3DXPARSER::AllocateAllBoneMatrices( LPD3DXFRAME pFrame )
{
	if (pFrame->pMeshContainer != nullptr)
	{
		if(FAILED(AllocateBoneMatrix(pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameSibling != nullptr)
	{
		if(FAILED(AllocateAllBoneMatrices(pFrame->pFrameSibling)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameFirstChild != nullptr)
	{
		if(FAILED(AllocateAllBoneMatrices(pFrame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
//
//======================================================================================
//X�t�@�C����ǂݍ���
//======================================================================================
HRESULT D3DXPARSER::LoadMeshFromX(LPDIRECT3DDEVICE9 pDevice9,LPSTR FileName)
{
	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����
	m_pHierarchy=new MY_HIERARCHY;
	if( FAILED( 
	D3DXLoadMeshHierarchyFromXA(FileName, D3DXMESH_32BIT, pDevice9, m_pHierarchy,
												 nullptr, &m_pFrameRoot, &m_pAnimController)))
	{
			MessageBoxA(nullptr, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���",FileName, MB_OK);
			return E_FAIL;
	}

	for (DWORD i = 0; i < m_pAnimController->GetNumAnimationSets(); i++)
	{
		HlAnimation_Desc *hlAnim = new HlAnimation_Desc();

		//�A�j���[�V�����擾
		m_pAnimController->GetAnimationSet(i, &(hlAnim->m_pAnimSet));

		//���[�v���Ԃ��w��
		hlAnim->m_LoopTime = 0;

		//����J�n���Ԃɂ����鎞�Ԃ��w��
		hlAnim->m_ShiftTime = HlAnimation_Desc::m_CShiftTime;

		//�A�j���[�V�����g���b�N�̏�����
		hlAnim->Enable = FALSE;

		//�e���x100
		hlAnim->Weight = 0.0f;

		//���x
		hlAnim->Speed = 0.1f;

		//���X�g�ɂԂ�����
		m_hlAnimationList.push_back(hlAnim);

	}



	//�{�[�����������肠��
	AllocateAllBoneMatrices(m_pFrameRoot);

	//���b�V���R���e�i�[�𓾂�
	m_pContainer = FindMeshContainer(m_pFrameRoot);

	return S_OK;
}

//======================================================================================
//���b�V���R���e�i��������
//======================================================================================
MYMESHCONTAINER* D3DXPARSER::FindMeshContainer(D3DXFRAME* pFrame)
{
	if (pFrame == nullptr) { return nullptr; }

	if (pFrame->pMeshContainer != nullptr)
	{
		return (MYMESHCONTAINER*)pFrame->pMeshContainer;
	}
	else
	{
		MYMESHCONTAINER* container = nullptr;
		container = FindMeshContainer(pFrame->pFrameFirstChild);
		
		if (container!= nullptr)
		{
			return container;
		}
	
	

		container = FindMeshContainer(pFrame->pFrameSibling);

		if (container != nullptr)
		{
			return container;
		}
	
	}

	return nullptr;
}
//======================================================================================
//VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
//�t���[�����̃��b�V�����Ƀ��[���h�ϊ��s����X�V����
//======================================================================================
VOID D3DXPARSER::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME *pFrame = (MYFRAME*)pFrameBase;	

	if (pParentMatrix != nullptr)
	{
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	if (pFrame->pFrameSibling != nullptr)
	{
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	if (pFrame->pFrameFirstChild != nullptr)
	{
		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}
//
//
//
int D3DXPARSER::GetNumVertices()
{
	return m_pContainer->MeshData.pMesh->GetNumVertices();
}
//
//
//
int D3DXPARSER::GetNumFaces()
{
	return m_pContainer->MeshData.pMesh->GetNumFaces();
}
//
//
//
int D3DXPARSER::GetNumMaterials()
{
	return m_pContainer->NumMaterials;
}
//
//
//
int D3DXPARSER::GetNumUVs()
{
	return m_pContainer->MeshData.pMesh->GetNumVertices();
}
//
//======================================================================================
//�w�肳�ꂽ�{�[�����e�����y�ڂ����_����Ԃ�
//======================================================================================
int D3DXPARSER::GetNumBoneVertices(int iBoneIndex)
{	
	return m_pContainer->pSkinInfo->GetNumBoneInfluences(iBoneIndex);
}
//
//======================================================================================
//�w�肳�ꂽ�{�[�����e�����y�ڂ����_�̃C���f�b�N�X��Ԃ� ��2�����́A�e�����󂯂钸�_�̃C���f�b�N�X�O���[�v���̃C���f�b�N�X�i�C���f�b�N�X���Ⴂ���j
//�Ⴆ�΃{�[���ɉe���������钸�_���S���Ƃ��āA���̃{�[���ɉe����������S�̒��_�̂���2�Ԗڂ̃C���f�b�N�X��m�肽���ꍇ�́AiIndexInGroup��1���w�肷��i0�X�^�[�g�Ȃ̂Łj
//======================================================================================
DWORD D3DXPARSER::GetBoneVerticesIndices(int iBoneIndex,int iIndexInGroup)
{
	int Num=m_pContainer->pSkinInfo->GetNumBoneInfluences(iBoneIndex);
	pVerts = new DWORD[Num];
	pWights = new float[Num];


	if(FAILED(m_pContainer->pSkinInfo->GetBoneInfluence(iBoneIndex,pVerts,pWights)))
	{
		return E_FAIL;
	}

	

	return pVerts[iIndexInGroup];
}
//
//======================================================================================
//�w�肳�ꂽ�{�[�����e�����y�ڂ����_�̃{�[���E�F�C�g��Ԃ� ��2�����́A�e�����󂯂钸�_�̃C���f�b�N�X�O���[�v���̃C���f�b�N�X�i�C���f�b�N�X���Ⴂ���j
//�Ⴆ�΃{�[���ɉe���������钸�_���S���Ƃ��āA���̃{�[���ɉe����������S�̒��_�̂���2�Ԗڂ̒��_�̃{�[���E�F�C�g��m�肽���ꍇ�́AiIndexInGroup��1���w�肷��i0�X�^�[�g�Ȃ̂Łj
//======================================================================================
double D3DXPARSER::GetBoneVerticesWeights(int iBoneIndex,int iIndexInGroup)
{
	int Num=m_pContainer->pSkinInfo->GetNumBoneInfluences(iBoneIndex);
	pVerts = new DWORD[Num];
	pWights=new float[Num];



	if(FAILED(m_pContainer->pSkinInfo->GetBoneInfluence(iBoneIndex,pVerts,pWights)))
	{
		return E_FAIL;
	}

	


	return pWights[iIndexInGroup];

}

//======================================================================================
//�f���[�g����
//======================================================================================
void D3DXPARSER::Delete()
{
	//for (UINT i = 0; i < BoneList.size(); i++) {
	//	delete BoneList[i];
	//	BoneList[i] = nullptr;
	//}
	//BoneList.clear();

	//for (UINT i = 0; i < ABList.size(); i++) {
	//	delete ABList[i];
	//	ABList[i] = nullptr;
	//}
	//ABList.clear();
	delete[] pVerts;
	delete[] pWights;

}

//
//======================================================================================
//���W
//======================================================================================
D3DXVECTOR3 D3DXPARSER::GetVertexCoord(DWORD Index)
{
	LPDIRECT3DVERTEXBUFFER9 pVB=nullptr;
	m_pContainer->MeshData.pMesh->GetVertexBuffer(&pVB);
	DWORD Stride=m_pContainer->MeshData.pMesh->GetNumBytesPerVertex();
	BYTE *pVertices=nullptr;
	D3DXVECTOR3* pCoord=nullptr;

	if(SUCCEEDED(pVB->Lock(0,0,(VOID**)&pVertices,0)))
	{
		pVertices+=Index*Stride;
		pCoord=(D3DXVECTOR3*)pVertices;
		pVB->Unlock();
	}
	SAFE_RELEASE( pVB );

	return *pCoord;
}
//
//======================================================================================
//�@��
//======================================================================================
D3DXVECTOR3 D3DXPARSER::GetNormal(DWORD Index)
{
	LPDIRECT3DVERTEXBUFFER9 pVB=nullptr;
	m_pContainer->MeshData.pMesh->GetVertexBuffer(&pVB);
	DWORD Stride=m_pContainer->MeshData.pMesh->GetNumBytesPerVertex();
	BYTE *pVertices=nullptr;
	D3DXVECTOR3* pNormal=nullptr;

	if(SUCCEEDED(pVB->Lock(0,0,(VOID**)&pVertices,0)))
	{
		pVertices+=Index*Stride;
		pVertices+=sizeof(D3DXVECTOR3);//���W���i�߂� 
		pNormal=(D3DXVECTOR3*)pVertices;
		pVB->Unlock();
	}
	SAFE_RELEASE( pVB );

	return *pNormal;
}
//
//======================================================================================
//�e�N�X�`���[���W
//======================================================================================
D3DXVECTOR2 D3DXPARSER::GetUV(DWORD Index)
{
	LPDIRECT3DVERTEXBUFFER9 pVB=nullptr;
	m_pContainer->MeshData.pMesh->GetVertexBuffer(&pVB);
	DWORD Stride=m_pContainer->MeshData.pMesh->GetNumBytesPerVertex();
	BYTE *pVertices=nullptr;
	D3DXVECTOR2* pUV=nullptr;

	if(SUCCEEDED(pVB->Lock(0,0,(VOID**)&pVertices,0)))
	{
		pVertices+=Index*Stride;
		pVertices+=sizeof(D3DXVECTOR3);//���W���i�߂�
		pVertices+=sizeof(D3DXVECTOR3);//�@�����i�߂�
		pUV=(D3DXVECTOR2*)pVertices;
		pVB->Unlock();
	}
	SAFE_RELEASE( pVB );

	return *pUV;
}
//
//======================================================================================
//�C���f�b�N�X�o�b�t�@���̎w�肵���ʒu�i�C���f�b�N�X�C���f�b�N�X�j�ɂ��钸�_�C���f�b�N�X��Ԃ�
//======================================================================================
int D3DXPARSER::GetIndex(DWORD Index)
{
	DWORD VertIndex=0;
	DWORD* pIndex=nullptr;
	m_pContainer->MeshData.pMesh->LockIndexBuffer(D3DLOCK_READONLY,(VOID**)&pIndex);

	VertIndex=pIndex[Index];

	m_pContainer->MeshData.pMesh->UnlockIndexBuffer();

	return VertIndex;
}
//
//
//
D3DXVECTOR4 D3DXPARSER::GetAmbient(int iIndex)
{
	D3DXCOLOR color;
	color=m_pContainer->pMaterials[iIndex].MatD3D.Ambient;
	return D3DXVECTOR4(color.a,color.r,color.g,color.b);
}
//
//
//
D3DXVECTOR4 D3DXPARSER::GetDiffuse(int iIndex)
{
	D3DXCOLOR color;
	color=m_pContainer->pMaterials[iIndex].MatD3D.Diffuse;
	return D3DXVECTOR4(color.a,color.r,color.g,color.b);
}
//
//
//
D3DXVECTOR4 D3DXPARSER::GetSpecular(int iIndex)
{
	D3DXCOLOR color;
	
	color=m_pContainer->pMaterials[iIndex].MatD3D.Specular;
	return D3DXVECTOR4(color.a,color.r,color.g,color.b);
}
//
//
//
CHAR* D3DXPARSER::GetTexturePath(int index)
{
	CHAR* p=nullptr;
	p=m_pContainer->pMaterials[index].pTextureFilename;
	return p;
}
//
//
//
float D3DXPARSER::GetSpecularPower(int iIndex)
{
	float power;
	
	power=m_pContainer->pMaterials[iIndex].MatD3D.Power;
	return power;
}
//
//
//���̃|���S�����A�ǂ̃}�e���A���ł��邩��Ԃ� 
int D3DXPARSER::GeFaceMaterialIndex(int iFaceIndex)
{
	int MaterialIndex=0;
	DWORD* pBuf=nullptr;
	if(SUCCEEDED(m_pContainer->MeshData.pMesh->LockAttributeBuffer(D3DLOCK_READONLY,&pBuf)))
	{
		MaterialIndex=pBuf[iFaceIndex];
	}
	else
	{
		MessageBoxA(0,"�����o�b�t�@�̃��b�N���s","",MB_OK);
	}
	return MaterialIndex;
}
//
//
//iFaceIndex�Ԗڂ̃|���S�����`������3���_�̒��ŁAiIndexInFace�Ԗ�[0,2]�̒��_�̃C���f�b�N�X��Ԃ�
int D3DXPARSER::GetFaceVertexIndex(int iFaceIndex,int iIndexInFace)
{
	//�C���f�b�N�X�o�b�t�@�[�𒲂ׂ�Ε�����
	DWORD VertIndex=0;
	DWORD* pIndex=nullptr;
	m_pContainer->MeshData.pMesh->LockIndexBuffer(D3DLOCK_READONLY,(VOID**)&pIndex);

	VertIndex=pIndex[iFaceIndex*3+iIndexInFace];

	m_pContainer->MeshData.pMesh->UnlockIndexBuffer();

	return VertIndex;
}
//
//
//
D3DXMATRIX D3DXPARSER::GetBindPose(int iBoneIndex)
{
	return *m_pContainer->pSkinInfo->GetBoneOffsetMatrix(iBoneIndex);
}
//
//
//���̊֐�����Ԃ��Ƃ�Update����Ɩ��ʂȂ̂ŁARender�֐����s����Update������̂Ƃ��Ă��̂܂ܓn���B
//�e�N���X�����̃N���X��UpdateMatrices�����s���Ȃ��ꍇ�́AUpdateMatrices���Ȃ��ƍs�񂪍ŐV�ɂȂ�Ȃ��̂ŗ��ӁB
D3DXMATRIX D3DXPARSER::GetNewPose(int iBoneIndex)
{
	MYMESHCONTAINER* pMyContaiber=(MYMESHCONTAINER*)m_pContainer;
	return *pMyContaiber->ppBoneMatrix[iBoneIndex];
}

//
//
//
CHAR* D3DXPARSER::GetBoneName(int iBoneIndex)
{
	return (CHAR*)m_pContainer->pSkinInfo->GetBoneName(iBoneIndex);
}
//
//
//
int D3DXPARSER::GetNumBones()
{
	return m_pContainer->pSkinInfo->GetNumBones();
}
//
//CD3DXSKINMESH::CD3DXSKINMESH()
//�R���X�g���N�^�[
CD3DXSKINMESH::CD3DXSKINMESH()
{
	ZeroMemory(this,sizeof(CD3DXSKINMESH));
	m_Scale=D3DXVECTOR3(1,1,1);
	m_AxisX = D3DXVECTOR3(1, 0, 0);
	m_AxisZ = D3DXVECTOR3(0, 0, 1);
}
//
//CD3DXSKINMESH::~CD3DXSKINMESH()
//�f�X�g���N�^�[
CD3DXSKINMESH::~CD3DXSKINMESH()
{
	delete[] m_BoneArray;
	delete[] m_pMaterial;
	SAFE_RELEASE(m_pVertexBuffer);
	for(int i=0;i<m_dwNumMaterial;i++)
	{
		//SAFE_RELEASE(m_ppIndexBuffer[i]);
	}
	delete[] m_ppIndexBuffer;
}
//
//
//������
HRESULT CD3DXSKINMESH::InitSM(HWND _hWnd,ID3D11Device* _pDevice,ID3D11DeviceContext* _pDeviceContext)
{
	m_hWnd = _hWnd;
	m_pDevice=_pDevice;
	m_pDeviceContext=_pDeviceContext;
	//D3d"9"�̃f�o�C�X�����A�S�Ă�D3DXMESH�̈����ɕK�v������
	// Direct3D"9"�I�u�W�F�N�g�̍쐬
	if( nullptr == ( m_pD3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		MessageBoxA(0,"Direct3D9�̍쐬�Ɏ��s���܂���","",MB_OK);
		return E_FAIL;
	}
	// DIRECT3D"9"�f�o�C�X�I�u�W�F�N�g�̍쐬
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferFormat =D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount=1;	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
									 D3DCREATE_HARDWARE_VERTEXPROCESSING,
									 &d3dpp, &m_pDevice9 ) ) )
	{
		if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
									 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									 &d3dpp, &m_pDevice9 ) ) )
		{
			MessageBoxA(0,"HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�",nullptr,MB_OK);
			if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
									 D3DCREATE_HARDWARE_VERTEXPROCESSING,
									 &d3dpp, &m_pDevice9 ) ) )
			{
				if( FAILED( m_pD3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
									 D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									 &d3dpp, &m_pDevice9 ) ) )
				{
					MessageBoxA(0,"DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���",nullptr,MB_OK);
					return E_FAIL;
				}
			}
		}
	}

	//D3D11�֘A�̏�����
	ID3DBlob *pCompiledShader=nullptr;
	ID3DBlob *pErrors=nullptr;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	SetShaderDirectory();
	if(FAILED(D3DX11CompileFromFile("Geometry_Material_Texture_Skin.hlsl",nullptr,nullptr,"VSSkin","vs_5_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
	{
//		int size=pErrors->GetBufferSize();
	//	char* ch=(char*)pErrors->GetBufferPointer();
		MessageBox(0,"hlsl�ǂݍ��ݎ��s",nullptr,MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if(FAILED(m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),nullptr,&m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0,"�o�[�e�b�N�X�V�F�[�_�[�쐬���s(CD3DXSKINMESH)",nullptr,MB_OK);
		return E_FAIL;
	}
	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_INDEX", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout)/sizeof(layout[0]);

	//���_�C���v�b�g���C�A�E�g���쐬
	if( FAILED( m_pDevice->CreateInputLayout( layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout ) ) )
		return FALSE;
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout( m_pVertexLayout );

	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if(FAILED(D3DX11CompileFromFile("Geometry_Material_Texture_Skin.hlsl",nullptr,nullptr,"PSSkin","ps_5_0",0,0,nullptr,&pCompiledShader,&pErrors,nullptr)))
	{
		MessageBox(0,"hlsl�ǂݍ��ݎ��s",nullptr,MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, &m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, "�s�N�Z���V�F�[�_�[�쐬���s", nullptr, MB_OK);
		return E_FAIL;
	}

	//���C�p�o�[�e�b�N�X�V�F�[�_�[
	D3DX11CompileFromFile("Geometry_Material_Texture_Skin.hlsl", nullptr, nullptr, "RayVS", "vs_5_0", 0, 0, nullptr, &pCompiledShader, &pErrors, nullptr);
	m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, &m_pLineVertexShader);

	//���C�p�o�[�e�b�N�X���C�A�E�g
	D3D11_INPUT_ELEMENT_DESC tmp[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	numElements = 1;
	memcpy(layout, tmp, sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);
	m_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pLineVertexLayout);

	//���C�p�s�N�Z���V�F�[�_�[
	D3DX11CompileFromFile("Geometry_Material_Texture_Skin.hlsl", nullptr, nullptr, "RayPS", "ps_5_0", 0, 0, nullptr, &pCompiledShader, &pErrors, nullptr);
	m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), nullptr, &m_pLinePixelShader);


	SAFE_RELEASE(pCompiledShader);
	D3D11_BUFFER_DESC cb;

	//�R���X�^���g�o�b�t�@�[�쐬�@���C�p
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(LINE_CBUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice->CreateBuffer(&cb, nullptr, &m_pLineConstantBuffer)))
	{
		return E_FAIL;
	}

	

	//�R���X�^���g�o�b�t�@�[0�쐬
	cb.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= sizeof( SHADER_SKIN_GLOBAL0 );
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	=0;
	cb.StructureByteStride=0;
	cb.Usage=D3D11_USAGE_DYNAMIC;

	if( FAILED(m_pDevice->CreateBuffer( &cb,nullptr,&m_pConstantBuffer0)))
	{
		return E_FAIL;
	}
	//�R���X�^���g�o�b�t�@�[1�쐬  
	cb.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= sizeof( SHADER_SKIN_GLOBAL1 );
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	=0;
	cb.StructureByteStride=0;
	cb.Usage=D3D11_USAGE_DYNAMIC;

	if( FAILED(m_pDevice->CreateBuffer( &cb,nullptr,&m_pConstantBuffer1)))
	{
		return E_FAIL;
	}
	//�R���X�^���g�o�b�t�@�[�{�[���p�@�쐬  
	cb.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= sizeof( SHADER_GLOBAL_BONES );
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	=0;
	cb.StructureByteStride=0;
	cb.Usage=D3D11_USAGE_DYNAMIC;

	if( FAILED(m_pDevice->CreateBuffer(&cb,nullptr,&m_pConstantBufferBone)))
	{
		return E_FAIL;
	}

	
	//���C�̃o�[�e�b�N�X�o�b�t�@�[�쐬
	D3DXVECTOR3 vPoint[2];
	vPoint[0] = D3DXVECTOR3(0, 0, 0);
	vPoint[1] = D3DXVECTOR3(0, 0, 1);

	ZeroMemory(&cb, sizeof(cb));
	cb.Usage = D3D11_USAGE_DEFAULT;
	cb.ByteWidth = sizeof(LINE_VERTEX) * 2;
	cb.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	cb.CPUAccessFlags = 0;
	cb.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vPoint;
	m_pDevice->CreateBuffer(&cb, &InitData, &m_pLineVertexBuffer);

	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc,sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState( &SamDesc, &m_pSampleLinear);

	return S_OK;
}
//
//HRESULT CD3DXSKINMESH::ReadSkinInfo(KFbxMesh* pFbxMesh,MY_SKINVERTEX* pvVB)
//X����X�L���֘A�̏���ǂݏo���@
HRESULT CD3DXSKINMESH::ReadSkinInfo(MY_SKINVERTEX* pvVB)
{
	//X���璊�o���ׂ����́A���_���Ƃ̃{�[���C���f�b�N�X�A���_���Ƃ̃{�[���E�F�C�g�A�o�C���h�s��A�|�[�Y�s��@��4����

	int i,k,m,n;
	int iNumVertex=m_pD3dxMesh->GetNumVertices();//���_��
	int iNumBone=0;//�{�[����


	//�{�[��	�̌��𓾂�
	iNumBone=m_pD3dxMesh->GetNumBones();
	//���ꂼ��̃{�[���ɉe�����󂯂钸�_�𒲂ׂ�@��������t�ɁA���_�x�[�X�Ń{�[���C���f�b�N�X�E�d�݂𐮓ڂ���
	for(i=0;i<iNumBone;i++)
	{
		int iNumIndex=m_pD3dxMesh->GetNumBoneVertices(i);//���̃{�[���ɉe�����󂯂钸�_��
		int* piIndex=new int[iNumIndex];
		for (k = 0; k < iNumIndex; k++) {
			piIndex[k] = m_pD3dxMesh->GetBoneVerticesIndices(i, k);
			m_pD3dxMesh->Delete();
		}


		double* pdWeight=new double[iNumIndex];
		for (k = 0; k < iNumIndex; k++) {
			pdWeight[k] = m_pD3dxMesh->GetBoneVerticesWeights(i, k);
			m_pD3dxMesh->Delete();
		}

		//���_������C���f�b�N�X�����ǂ��āA���_�T�C�h�Ő�������
		for(k=0;k<iNumIndex;k++)
		{
			//X��CG�\�t�g���{�[��4�{�ȓ��Ƃ͌���Ȃ��B5�{�ȏ�̏ꍇ�́A�d�݂̑傫������4�{�ɍi�� 

			//�E�F�C�g�̑傫�����Ƀ\�[�g�i�o�u���\�[�g�j
			for(m=4;m>1;m--)
			{
				for(n=1;n<m;n++)
				{
					if(pvVB[ piIndex[k] ].bBoneWeight[n-1] < pvVB[ piIndex[k] ].bBoneWeight[n])
					{
						float tmp=pvVB[ piIndex[k] ].bBoneWeight[n-1];
						pvVB[ piIndex[k] ].bBoneWeight[n-1]=pvVB[ piIndex[k] ].bBoneWeight[n];
						pvVB[ piIndex[k] ].bBoneWeight[n]=tmp;		
						int itmp=pvVB[ piIndex[k] ].bBoneIndex[n-1];
						pvVB[ piIndex[k] ].bBoneIndex[n-1]=pvVB[ piIndex[k] ].bBoneIndex[n];
						pvVB[ piIndex[k] ].bBoneIndex[n]=itmp;		
					}
				}
			}		
			//�\�[�g��́A�Ō�̗v�f�Ɉ�ԏ������E�F�C�g�������Ă���͂��B
			bool flag=false;
			for(m=0;m<4;m++)
			{
				if(pvVB[ piIndex[k] ].bBoneWeight[m]==0)
				{
					flag=true;
					pvVB[ piIndex[k] ].bBoneIndex[ m]=i;
					pvVB[ piIndex[k] ].bBoneWeight[m]=pdWeight[k];
					break;
				}
			}
			if(flag==false)
			{
				pvVB[ piIndex[k] ].bBoneIndex[ 3]=i;
				pvVB[ piIndex[k] ].bBoneWeight[3]=pdWeight[k];
				break;
			}

		}
		delete piIndex;
		delete pdWeight;


	}

	
	//
	//�{�[���𐶐�
	m_iNumBone=iNumBone;
	m_BoneArray=new BONE[iNumBone];
	//�|�[�Y�s��𓾂� �����|�[�Y
	for(i=0;i<m_iNumBone;i++)
	{
		m_BoneArray[i].mBindPose=m_pD3dxMesh->GetBindPose(i);
	}	
	

	return S_OK;
}
//
//HRESULT CD3DXSKINMESH::CreateFromX(CHAR* szFileName)
//X����X�L�����b�V�����쐬����@�@���Ӂj�f�ށiX)�̂ق��́A�O�p�|���S���ɂ��邱��
HRESULT CD3DXSKINMESH::CreateFromX(CHAR* szFileName)
{
	//X�t�@�C���ǂݍ���
	m_pD3dxMesh=new D3DXPARSER;
	m_pD3dxMesh->LoadMeshFromX(m_pDevice9,szFileName);

	//���O�ɒ��_���A�|���S�������𒲂ׂ�
	m_dwNumVert=m_pD3dxMesh->GetNumVertices();
	m_dwNumFace=m_pD3dxMesh->GetNumFaces();
	m_dwNumUV=m_pD3dxMesh->GetNumUVs();
	if(m_dwNumVert<m_dwNumUV)//Direct3D�ł�UV�̐��������_���K�v
	{
		//���L���_���ŁA���_��������Ȃ���
		MessageBox(0,"Direct3D�́AUV�̐��������_���K�v�ł��iUV��u���ꏊ���K�v�ł��j�e�N�X�`���[�͐������\���Ȃ��Ǝv���܂�",nullptr,MB_OK);
		return E_FAIL;
	}
	//�ꎞ�I�ȃ������m�ہi���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�j
	MY_SKINVERTEX* pvVB =new MY_SKINVERTEX[m_dwNumVert];
	int* piFaceBuffer=new int[ m_dwNumFace*3 ];//�R���_�|���S���Ȃ̂ŁA1�t�F�C�X=3���_(3�C���f�b�N�X)

	//���_�ǂݍ���
	for(int i=0;i<m_dwNumVert;i++)
	{
		D3DXVECTOR3 v=m_pD3dxMesh->GetVertexCoord(i);
		pvVB[i].vPos.x=v.x;
		pvVB[i].vPos.y=v.y;
		pvVB[i].vPos.z=v.z;
	}
	//�|���S�����i���_�C���f�b�N�X�j�ǂݍ���
	for(int i=0;i<m_dwNumFace*3;i++)
	{
		piFaceBuffer[i]=m_pD3dxMesh->GetIndex(i);
	}
	//�@���ǂݍ���
	for(int i=0;i<m_dwNumVert;i++)
	{
		D3DXVECTOR3 v=m_pD3dxMesh->GetNormal(i);
		pvVB[i].vNorm.x=v.x;
		pvVB[i].vNorm.y=v.y;
		pvVB[i].vNorm.z=v.z;
	}
	//�e�N�X�`���[���W�ǂݍ���
	for(int i=0;i<m_dwNumVert;i++)
	{
		D3DXVECTOR3 v=m_pD3dxMesh->GetUV(i);
		pvVB[i].vTex.x=v.x;
		pvVB[i].vTex.y=v.y;
	}
	//�}�e���A���ǂݍ���
	m_dwNumMaterial=m_pD3dxMesh->GetNumMaterials();
	m_pMaterial=new MY_SKINMATERIAL[m_dwNumMaterial];

	//�}�e���A���̐������C���f�b�N�X�o�b�t�@�[���쐬
	m_ppIndexBuffer=new ID3D11Buffer*[m_dwNumMaterial];
	for(int i=0;i<m_dwNumMaterial;i++)
	{
		//����	
		m_pMaterial[i].Ka.x=m_pD3dxMesh->GetAmbient(i).y;
		m_pMaterial[i].Ka.y=m_pD3dxMesh->GetAmbient(i).z;
		m_pMaterial[i].Ka.z=m_pD3dxMesh->GetAmbient(i).w;
		m_pMaterial[i].Ka.w=m_pD3dxMesh->GetAmbient(i).x;
		//�g�U���ˌ�	
		m_pMaterial[i].Kd.x=m_pD3dxMesh->GetDiffuse(i).y;
		m_pMaterial[i].Kd.y=m_pD3dxMesh->GetDiffuse(i).z;
		m_pMaterial[i].Kd.z=m_pD3dxMesh->GetDiffuse(i).w;
		m_pMaterial[i].Kd.w=m_pD3dxMesh->GetDiffuse(i).x;
		//���ʔ��ˌ�
		m_pMaterial[i].Ks.x=m_pD3dxMesh->GetSpecular(i).y;
		m_pMaterial[i].Ks.y=m_pD3dxMesh->GetSpecular(i).z;
		m_pMaterial[i].Ks.z=m_pD3dxMesh->GetSpecular(i).w;
		m_pMaterial[i].Ks.w=m_pD3dxMesh->GetSpecular(i).x;

		//�e�N�X�`���[�i�f�B�t���[�Y�e�N�X�`���[�̂݁j
		char* name=m_pD3dxMesh->GetTexturePath(i);
		if(name)
		{
			strcpy(m_pMaterial[i].szTextureName,name);
		}
		//�e�N�X�`���[���쐬
		if(m_pMaterial[i].szTextureName[0] != 0 && FAILED(D3DX11CreateShaderResourceViewFromFileA( m_pDevice, m_pMaterial[i].szTextureName, nullptr, nullptr, &m_pMaterial[i].pTexture, nullptr )))//��΃p�X�t�@�C�����́A�܂����s����Ǝv�����A�A�A
		{
				MessageBox(0,"�e�N�X�`���[�ǂݍ��ݎ��s(CD3DXSKINMESH)",nullptr,MB_OK);
				return E_FAIL;
		}
		
		//���̃}�e���A���ł���C���f�b�N�X�z����̊J�n�C���f�b�N�X�𒲂ׂ�@����ɃC���f�b�N�X�̌������ׂ�
		int iCount=0;
		int* pIndex=new int[m_dwNumFace*3];//�Ƃ肠�����A���b�V�����̃|���S�����Ń������m�ہi�X�̃|���S���O���[�v�͂��Ȃ炸����ȉ��ɂȂ邪�j
	
		for(int k=0;k<m_dwNumFace;k++)
		{
			if( i == m_pD3dxMesh->GeFaceMaterialIndex(k))//���� i == k�Ԗڂ̃|���S���̃}�e���A���ԍ� �Ȃ�
			{
				pIndex[iCount]=m_pD3dxMesh->GetFaceVertexIndex(k,0);//k�Ԗڂ̃|���S������钸�_�̃C���f�b�N�X�@1��
				pIndex[iCount+1]=m_pD3dxMesh->GetFaceVertexIndex(k,1);//2��
				pIndex[iCount+2]=m_pD3dxMesh->GetFaceVertexIndex(k,2);//3��
				iCount+=3;
			}
		}
		if(iCount>0) CreateIndexBuffer(iCount*sizeof(int),pIndex ,&m_ppIndexBuffer[i]);
		delete pIndex;
		m_pMaterial[i].dwNumFace=iCount/3;//���̃}�e���A�����̃|���S����
		
	}
	//�X�L�����i�W���C���g�A�E�F�C�g�@�j�ǂݍ���
	ReadSkinInfo(pvVB);
	//�o�[�e�b�N�X�o�b�t�@�[���쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( MY_SKINVERTEX ) *m_dwNumVert;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVB;
	if( FAILED( m_pDevice->CreateBuffer( &bd, &InitData, &m_pVertexBuffer ) ) )
		return FALSE;

	//�ꎞ�I�ȓ��ꕨ�́A�s�v
	delete piFaceBuffer;
	if(pvVB) delete pvVB;

	return S_OK;
}
//
//HRESULT CD3DXSKINMESH::CreateIndexBuffer(DWORD dwSize,int* pIndex,ID3D11Buffer** ppIndexBuffer)
//Direct3D�̃C���f�b�N�X�o�b�t�@�[�쐬
HRESULT CD3DXSKINMESH::CreateIndexBuffer(DWORD dwSize,int* pIndex,ID3D11Buffer** ppIndexBuffer)
{
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = dwSize;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pIndex;
	InitData.SysMemPitch=0;
	InitData.SysMemSlicePitch=0;
	if( FAILED( m_pDevice->CreateBuffer( &bd, &InitData, ppIndexBuffer) ) )
	{
		return FALSE;
	}
	
	return S_OK;
}

//
//void CD3DXSKINMESH::SetNewPoseMatrices(int frame)
//�{�[�������̃|�[�Y�ʒu�ɃZ�b�g����
void CD3DXSKINMESH::SetNewPoseMatrices(int iFrame)
{
	//�]�ރt���[����Update���邱�ƁB���Ȃ��ƍs�񂪍X�V����Ȃ�
	//m_pD3dxMesh->UpdateFrameMatrices(m_pD3dxMesh->m_pFrameRoot)�������_�����O���Ɏ��s���邱��
	
	//�܂��A�A�j���[�V�������ԂɌ��������s����X�V����̂�D3DXMESH�ł�
	//�A�j���[�V�����R���g���[���[���i���Łj����Ă������̂Ȃ̂ŁA�A�j���[�V�����R���g���[���[
	//���g���ăA�j����i�s�����邱�Ƃ��K�v
	//	m_pD3dxMesh->m_pAnimController->AdvanceTime(....)�������_�����O���Ɏ��s���邱��

	for(int i=0;i<m_iNumBone;i++)
	{
		m_BoneArray[i].mNewPose=m_pD3dxMesh->GetNewPose(i);
	}
}
//
//D3DXMATRIX CD3DXSKINMESH::GetCurrentPoseMatrix(int index)
//���́i���݂́j�|�[�Y�s���Ԃ�
D3DXMATRIX CD3DXSKINMESH::GetCurrentPoseMatrix(int index)
{
	D3DXMATRIX ret=m_BoneArray[index].mBindPose*m_BoneArray[index].mNewPose;	
	return ret;
}
//
//D3DXMATRIX CD3DXSKINMESH::GetBindPoseMatrix(int index)
//�o�C���h�|�[�Y�s���Ԃ�
D3DXMATRIX CD3DXSKINMESH::GetBindPoseMatrix(int index)
{
	return m_BoneArray[index].mBindPose;
}
//
//
//
CHAR* CD3DXSKINMESH::GetBoneNames(int iBoneIndex)
{
	return m_pD3dxMesh->GetBoneName(iBoneIndex);
}
//
//void CD3DXSKINMESH::Render()
//�����_�����O
void CD3DXSKINMESH::Render(D3DXMATRIX& _mView, D3DXMATRIX& _mProj, D3DXVECTOR3& _vLight, D3DXVECTOR3& _Eye)
{
	m_View = _mView;
	m_Proj = _mProj;
	D3D11_MAPPED_SUBRESOURCE pData;

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pDeviceContext->VSSetShader(m_pVertexShader,nullptr,0);
	m_pDeviceContext->PSSetShader(m_pPixelShader,nullptr,0);

	//���[���h�g�����X�t�H�[��
	D3DXMATRIX Scale,Yaw,Pitch,Roll,Tran;
	D3DXMatrixScaling(&Scale,m_Scale.x,m_Scale.y,m_Scale.z);
	D3DXMatrixRotationY(&Yaw,m_Yaw);
	D3DXMatrixRotationX(&Pitch,m_Pitch);
	D3DXMatrixTranslation(&Tran, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixRotationZ(&Roll,m_Roll);
	m_Rotation = Yaw*Pitch*Roll;
	m_World=Scale*m_Rotation*Tran;	

	//��]�ɂ��A���[�J�������Ȃ���
	D3DXVec3TransformCoord(&m_AxisX, &D3DXVECTOR3(1, 0, 0), &m_Rotation);
	D3DXVec3TransformCoord(&m_AxisZ, &D3DXVECTOR3(0, 0, 1), &m_Rotation);

	
	//�A�j���[�V�����t���[����i�߂�@�X�L�����X�V
	static int iFrame=0;
	/*iFrame;
	if(iFrame>=3600) iFrame=0;*/

	////���݂̃A�j���[�V�����ԍ���K��
	//m_pD3dxMesh->m_pAnimController->SetTrackAnimationSet(0, m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]->m_pAnimSet);

	////0(�Đ�����)�g���b�N����g���b�N�f�X�N���Z�b�g����
	//m_pD3dxMesh->m_pAnimController->SetTrackDesc(0, m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]);


	////�A�j���[�V�������Ԃ��X�V
	//m_pD3dxMesh->m_AnimTime++;



	SetNewPoseMatrices(4);
	if( SUCCEEDED(m_pDeviceContext->Map(m_pConstantBufferBone,0, D3D11_MAP_WRITE_DISCARD,0,&pData)))
	{
		SHADER_GLOBAL_BONES sg;	
		for(int i=0;i<m_iNumBone;i++)
		{
			D3DXMATRIX mat=GetCurrentPoseMatrix(i);
			D3DXMatrixTranspose(&mat,&mat);
			sg.mBone[i]=mat;
		}
		memcpy_s( pData.pData, pData.RowPitch, (void*)&sg,sizeof(SHADER_GLOBAL_BONES));
		m_pDeviceContext->Unmap(m_pConstantBufferBone,0);
	}
	m_pDeviceContext->VSSetConstantBuffers(2,1,&m_pConstantBufferBone);
	m_pDeviceContext->PSSetConstantBuffers(2,1,&m_pConstantBufferBone);	

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g�i�o�[�e�b�N�X�o�b�t�@�[�͈�ł����j
	UINT stride = sizeof(MY_SKINVERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0,1,&m_pVertexBuffer,&stride,&offset);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�J�����ʒu���V�F�[�_�[�ɓn��
	if( SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer0,0,D3D11_MAP_WRITE_DISCARD,0,&pData)))
	{
		SHADER_SKIN_GLOBAL0 sg;		
		sg.vLightDir=D3DXVECTOR4(_vLight.x, _vLight.y, _vLight.z,0.0f);
		sg.vEye=D3DXVECTOR4(_Eye.x,_Eye.y,_Eye.z,0);
		memcpy_s( pData.pData, pData.RowPitch, (void*)&sg,sizeof(SHADER_SKIN_GLOBAL0));
		m_pDeviceContext->Unmap(m_pConstantBuffer0,0);
	}
	m_pDeviceContext->VSSetConstantBuffers(0,1,&m_pConstantBuffer0);
	m_pDeviceContext->PSSetConstantBuffers(0,1,&m_pConstantBuffer0);

	//�}�e���A���̐������A���ꂼ��̃}�e���A���̃C���f�b�N�X�o�b�t�@�|��`��
	for(int i=0;i<m_dwNumMaterial;i++)
	{
		//�g�p����Ă��Ȃ��}�e���A���΍�
		if(m_pMaterial[i].dwNumFace==0)
		{
			continue;
		}
		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		stride = sizeof( int );
		offset = 0;
		m_pDeviceContext->IASetIndexBuffer(m_ppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0 );		

		//�}�e���A���̊e�v�f�ƕϊ��s����V�F�[�_�[�ɓn��			
		D3D11_MAPPED_SUBRESOURCE pData;
		if( SUCCEEDED( m_pDeviceContext->Map( m_pConstantBuffer1,0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
		{
			SHADER_SKIN_GLOBAL1 sg;
			sg.mW=m_World;
			D3DXMatrixTranspose( &sg.mW, &sg.mW );
			sg.mWVP=m_World*m_View*m_Proj;
			D3DXMatrixTranspose( &sg.mWVP, &sg.mWVP );
			sg.vAmbient=m_pMaterial[i].Ka;
			sg.vDiffuse=m_pMaterial[i].Kd;
			sg.vSpecular=m_pMaterial[i].Ks;
			memcpy_s( pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_SKIN_GLOBAL1));
			m_pDeviceContext->Unmap(m_pConstantBuffer1,0);
		}
		m_pDeviceContext->VSSetConstantBuffers(1,1,&m_pConstantBuffer1);
		m_pDeviceContext->PSSetConstantBuffers(1,1,&m_pConstantBuffer1);
		//�e�N�X�`���[���V�F�[�_�[�ɓn��
		if(m_pMaterial[i].szTextureName[0] != NULL)
		{
			m_pDeviceContext->PSSetSamplers(0,1,&m_pSampleLinear);
			m_pDeviceContext->PSSetShaderResources(0,1,&m_pMaterial[i].pTexture);
		}
		else
		{
			ID3D11ShaderResourceView* Nothing[1]={0};
			m_pDeviceContext->PSSetShaderResources(0,1,Nothing);
		}
		//Draw
		m_pDeviceContext->DrawIndexed(m_pMaterial[i].dwNumFace*3,0,0);
	}


	//�A�j���i�s
	if(m_pD3dxMesh->m_pAnimController)
	{
		m_pD3dxMesh->AdavancedTime(m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]->Speed);
	}

	
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	m_pD3dxMesh->UpdateFrameMatrices(m_pD3dxMesh->m_pFrameRoot,&m);

	//�Đ����̃A�j���[�V������z��Ɋi�[����
	m_pD3dxMesh->m_pAnimController->GetTrackDesc(0, m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]);
}

BOOL D3DXPARSER::AdavancedTime(float time)
{
	

	//���������ۂ��𔻒�
	m_hlAnimationList[m_CurrentTrack]->Weight += time;
	if (m_hlAnimationList[m_CurrentTrack]->Weight <= m_hlAnimationList[m_CurrentTrack]->m_ShiftTime)
	{
		//�������@�E�F�C�g���Z�o
		
		float Weight = m_hlAnimationList[m_CurrentTrack]->Weight / m_hlAnimationList[m_CurrentTrack]->m_ShiftTime;

		//�E�F�C�g��o�^
		m_pAnimController->SetTrackWeight(0, Weight);	//���݂̃A�j���[�V����
		m_pAnimController->SetTrackWeight(1, false);	//�O�̃A�j���[�V�����𖳌��ɂ���

	}

	//�A�j���[�V�������ԃf�[�^�̍X�V
	

	if (!m_AnimStopFlg)
	{
		m_pAnimController->AdvanceTime(m_hlAnimationList[m_CurrentTrack]->Speed, nullptr);
	}
	else
	{
		m_pAnimController->AdvanceTime(0, nullptr);
	}

	return TRUE;
}

VOID CD3DXSKINMESH::ChangeAnim(DWORD _NewAnimNum)
{
	//�A�j���[�V�����^�C����������
	m_pD3dxMesh->m_AnimTime = 0;

	//�A�j���[�V�����؂�ւ��ɍ������s��
	//������s���ƃA�j���[�V�����ƃA�j���[�V�����̐؂�ւ�����
	//�p�b�Ɛ؂�ւ�炸���炩�ɃA�j���[�V�����ł���B

	//�A�j���[�V�������J�n
	m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]->Enable = TRUE;
	m_pD3dxMesh->m_hlAnimationList[_NewAnimNum]->Enable = TRUE;

	//���̃A�j���[�V�������g���b�N1�Ɉڍs���g���b�N�̐ݒ�l���ڍs
	m_pD3dxMesh->m_pAnimController->SetTrackAnimationSet(1, m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]->m_pAnimSet);
	m_pD3dxMesh->m_pAnimController->SetTrackDesc(1, m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]);

	//�V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
	m_pD3dxMesh->m_pAnimController->SetTrackAnimationSet(0, m_pD3dxMesh->m_hlAnimationList[_NewAnimNum]->m_pAnimSet);

	//�g���b�N�̍���������
	m_pD3dxMesh->m_pAnimController->SetTrackEnable(0, TRUE);
	m_pD3dxMesh->m_pAnimController->SetTrackEnable(1, TRUE);

	//�E�F�C�g���Ԃ�L����
	m_pD3dxMesh->m_hlAnimationList[m_pD3dxMesh->m_CurrentTrack]->Weight = 0.0f;
	m_pD3dxMesh->m_hlAnimationList[_NewAnimNum]->Weight = 0.0f;

	//�ύX�O�̃A�j���[�V�����ԍ��̕ۑ�
	m_pD3dxMesh->m_BeforeTrack = m_pD3dxMesh->m_CurrentTrack;

	

	//�V�K�A�j���[�V�����ɕύX
	m_pD3dxMesh->m_CurrentTrack = _NewAnimNum;


}

void CD3DXSKINMESH::RenderNoAnim(D3DXMATRIX& World)
{
	D3D11_MAPPED_SUBRESOURCE pData;

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

	//���[���h�s��
	D3DXMATRIX Scale;
	D3DXMatrixScaling(&Scale, m_Scale.x, m_Scale.y, m_Scale.z);
	m_World = World;

	//�A�j���[�V�����t���[����i�߂�@�X�L�����X�V

	D3DXMATRIX Id;
	D3DXMatrixIdentity(&Id);
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBufferBone, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SHADER_GLOBAL_BONES sg;
		for (int i = 0; i<m_iNumBone; i++)
		{
			sg.mBone[i] = Id;
		}
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_GLOBAL_BONES));
		m_pDeviceContext->Unmap(m_pConstantBufferBone, 0);
	}
	m_pDeviceContext->VSSetConstantBuffers(2, 1, &m_pConstantBufferBone);
	m_pDeviceContext->PSSetConstantBuffers(2, 1, &m_pConstantBufferBone);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g�i�o�[�e�b�N�X�o�b�t�@�[�͈�ł����j
	UINT stride = sizeof(MY_SKINVERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�J�����ʒu���V�F�[�_�[�ɓn��
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SHADER_SKIN_GLOBAL0 sg;
		sg.vLightDir = D3DXVECTOR4(1, 1, -1, 0.0f);
		sg.vEye = D3DXVECTOR4(m_Eye.x, m_Eye.y, m_Eye.z, 0);
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_SKIN_GLOBAL0));
		m_pDeviceContext->Unmap(m_pConstantBuffer0, 0);
	}
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer0);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer0);

	//�}�e���A���̐������A���ꂼ��̃}�e���A���̃C���f�b�N�X�o�b�t�@�|��`��
	for (int i = 0; i<m_dwNumMaterial; i++)
	{
		//�g�p����Ă��Ȃ��}�e���A���΍�
		if (m_pMaterial[i].dwNumFace == 0)
		{
			continue;
		}
		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		stride = sizeof(int);
		offset = 0;
		m_pDeviceContext->IASetIndexBuffer(m_ppIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

		//�}�e���A���̊e�v�f�ƕϊ��s����V�F�[�_�[�ɓn��			
		D3D11_MAPPED_SUBRESOURCE pData;
		if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer1, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			SHADER_SKIN_GLOBAL1 sg;
			sg.mW = Scale*m_World;
			D3DXMatrixTranspose(&sg.mW, &sg.mW);
			sg.mWVP = Scale*m_World*m_View*m_Proj;
			D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
			sg.vAmbient = m_pMaterial[i].Ka;
			sg.vDiffuse = m_pMaterial[i].Kd;
			sg.vSpecular = m_pMaterial[i].Ks;
			memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_SKIN_GLOBAL1));
			m_pDeviceContext->Unmap(m_pConstantBuffer1, 0);
		}
		m_pDeviceContext->VSSetConstantBuffers(1, 1, &m_pConstantBuffer1);
		m_pDeviceContext->PSSetConstantBuffers(1, 1, &m_pConstantBuffer1);
		//�e�N�X�`���[���V�F�[�_�[�ɓn��
		if (m_pMaterial[i].szTextureName[0] != NULL)
		{
			m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
			m_pDeviceContext->PSSetShaderResources(0, 1, &m_pMaterial[i].pTexture);
		}
		else
		{
			ID3D11ShaderResourceView* Nothing[1] = { 0 };
			m_pDeviceContext->PSSetShaderResources(0, 1, Nothing);
		}
		//Draw
		m_pDeviceContext->DrawIndexed(m_pMaterial[i].dwNumFace * 3, 0, 0);
	}
	//m_pD3dxMesh->UpdateFrameMatrices(m_pD3dxMesh->m_pFrameRoot,&m_World);
}

void CD3DXSKINMESH::RenderRay(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vRayDir, float RayLength)
{
	D3DXMATRIX mWorld, mScale, mRotation, mPosition;

	m_View = mView;
	m_Proj = mProj;

	D3DXMatrixScaling(&mScale, RayLength, RayLength, RayLength);
	D3DXMatrixRotationY(&mRotation, m_Yaw);
	D3DXMatrixTranslation(&mPosition, m_Pos.x, m_Pos.y+1, m_Pos.z);
	mWorld = mScale*mRotation*mPosition;

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pDeviceContext->VSSetShader(m_pLineVertexShader, nullptr, 0);
	m_pDeviceContext->PSSetShader(m_pLinePixelShader, nullptr, 0);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	LINE_CBUFFER cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pLineConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n��
		cb.mWVP = mWorld*m_View*m_Proj;
		D3DXMatrixTranspose(&cb.mWVP, &cb.mWVP);
		//�J���[��n��
		cb.Color = D3DXVECTOR4(1, 0, 0, 1);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pLineConstantBuffer, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���A�ǂ̃V�F�[�_�[�Ŏg�������w��
	m_pDeviceContext->VSSetConstantBuffers(2, 1, &m_pLineConstantBuffer);//�o�[�e�b�N�X�o�b�t�@�[�Ŏg��
	m_pDeviceContext->PSSetConstantBuffers(2, 1, &m_pLineConstantBuffer);//�s�N�Z���V�F�[�_�[�ł̎g��
																		   //�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(LINE_VERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pLineVertexBuffer, &stride, &offset);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout(m_pLineVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//�v���~�e�B�u�������_�����O
	m_pDeviceContext->Draw(2, 0);

	
}


void D3DXPARSER::SetStop(bool _flag)
{
	m_AnimStopFlg = _flag;
}