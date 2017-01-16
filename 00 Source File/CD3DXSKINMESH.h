#pragma once
#include "BASE.h"


#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define MAX_BONES 255

//=======================================================================================
//�}�N��
//=======================================================================================
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=nullptr; } }
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }

//=======================================================================================
//X�ǂݍ��݊֐��̎Q��
//=======================================================================================
HRESULT InitX(CHAR* szFileName);
void DestroyX();



//=======================================================================================
//�I���W�i���@�}�e���A���\����
//=======================================================================================
struct MY_SKINMATERIAL
{
	CHAR szName[110];
	D3DXVECTOR4 Ka;//�A���r�G���g
	D3DXVECTOR4 Kd;//�f�B�t���[�Y
	D3DXVECTOR4 Ks;//�X�y�L�����[
	CHAR szTextureName[512];//�e�N�X�`���[�t�@�C����
	ID3D11ShaderResourceView* pTexture;
	DWORD dwNumFace;//���̃}�e���A���ł���|���S����
	MY_SKINMATERIAL()
	{
		ZeroMemory(this,sizeof(MY_SKINMATERIAL));
	}
	~MY_SKINMATERIAL()
	{
		SAFE_RELEASE(pTexture);
	}
};

//=======================================================================================
//���_�\����
//=======================================================================================
struct MY_SKINVERTEX
{
	D3DXVECTOR3 vPos;//���_�ʒu
	D3DXVECTOR3 vNorm;//���_�@��
	D3DXVECTOR2 vTex;//UV���W
	UINT bBoneIndex[4];//�{�[���@�ԍ�
	float bBoneWeight[4];//�{�[���@�d��
	MY_SKINVERTEX()
	{
		ZeroMemory(this,sizeof(MY_SKINVERTEX));
	}
};
//=======================================================================================
//�{�[���\����
//=======================================================================================
struct BONE
{
	D3DXMATRIX mBindPose;//�����|�[�Y�i�����ƕς��Ȃ��j
	D3DXMATRIX mNewPose;//���݂̃|�[�Y�i���̓s�x�ς��j
	DWORD dwNumChild;//�q�̐�
	int iChildIndex[50];//�����̎q�́h�C���f�b�N�X" 50�܂�
	CHAR Name[256];

	BONE()
	{
		ZeroMemory(this,sizeof(BONE));
		D3DXMatrixIdentity(&mBindPose);
		D3DXMatrixIdentity(&mNewPose);
	}
};
//
//

//=======================================================================================
//�h���t���[���\���� (���ꂼ��̃��b�V���p�̍ŏI���[���h�s���ǉ�����j
//=======================================================================================
struct MYFRAME: public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
};
//=======================================================================================
//�h�����b�V���R���e�i�[�\����(
//�R���e�i�[���e�N�X�`���𕡐����Ă�悤�Ƀ|�C���^�[�̃|�C���^�[��ǉ�����j
//=======================================================================================
struct MYMESHCONTAINER: public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight;//�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
	DWORD dwBoneNum;//�{�[���̐�
	LPD3DXBUFFER pBoneBuffer;//�{�[���E�e�[�u��
	D3DXMATRIX** ppBoneMatrix;//�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
	D3DXMATRIX* pBoneOffsetMatrices;//�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[	
};

//=======================================================================================
//X�t�@�C�����̃A�j���[�V�����K�w��ǂ݉����Ă����N���X��h��������B
//ID3DXAllocateHierarchy�͔h�����邱�Ƒz�肵�Đ݌v����Ă���B
//=======================================================================================
class MY_HIERARCHY: public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY(){}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR ,CONST D3DXMESHDATA* ,CONST D3DXMATERIAL* , 
		CONST D3DXEFFECTINSTANCE* , DWORD , CONST DWORD *, LPD3DXSKININFO , LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME );
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER );	
};

class HlAnimation_Desc : public D3DXTRACK_DESC
{
public:
	HlAnimation_Desc();
	~HlAnimation_Desc();

	
	ID3DXAnimationSet* m_pAnimSet;
	float			   m_LoopTime;
	float			   m_ShiftTime;

	
	//�A�j���[�V������؂�ւ�����
	static const float m_CShiftTime;

};

class D3DXPARSER
{
private:

public:
	//=======================================================================================
	//�X�L�����b�V���ɕK�v�ȕϐ�
	//=======================================================================================
	MY_HIERARCHY cHierarchy;
	MY_HIERARCHY* m_pHierarchy;
	LPD3DXFRAME m_pFrameRoot;
	MYMESHCONTAINER* m_pContainer;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	HRESULT LoadMeshFromX(LPDIRECT3DDEVICE9,LPSTR);
	HRESULT AllocateBoneMatrix(  LPD3DXMESHCONTAINER  );
	HRESULT AllocateAllBoneMatrices( LPD3DXFRAME  );
	MYMESHCONTAINER* FindMeshContainer(D3DXFRAME* pFrame);
	DWORD *pVerts;
	float *pWights;
	VOID UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );

	//=======================================================================================
	//�{�[�����폜���邽�߂̃��X�g
	//=======================================================================================
	static std::vector<DWORD *>BoneList;
	static std::vector<float *>ABList;


	//=======================================================================================
	//�X�L�����b�V���ɕK�v�Ȋ֐�
	//=======================================================================================
	int GetNumVertices();					//���_�̐����擾
	int GetNumFaces();						//�ʂ̐����擾
	int GetNumMaterials();					//�}�e���A���̐����擾
	int GetNumUVs();						//UV�̐����擾
	int GetNumBones();						//�{�[���̐����擾
	int GetNumBoneVertices(int iBoneIndex);	//�{�[���̒��_�̐����擾
	DWORD GetBoneVerticesIndices(int iBoneIndex,int iIndexInGroup);		//�{�[���̃C���f�b�N�X���擾
	double GetBoneVerticesWeights(int iBoneIndex,int iIndexInGroup);	//�{�[���̃E�F�C�g���擾


	D3DXVECTOR3 GetVertexCoord(DWORD iIndex);
	D3DXVECTOR3 GetNormal(DWORD iIndex);
	D3DXVECTOR2 GetUV(DWORD iIndex);
	int GetIndex(DWORD iIndex);
	D3DXVECTOR4 GetAmbient(int iIndex);
	D3DXVECTOR4 GetDiffuse(int iIndex);
	D3DXVECTOR4 GetSpecular(int iIndex);
	CHAR* GetTexturePath(int index);
	float GetSpecularPower(int iIndex);
	int GeFaceMaterialIndex(int iFaceIndex);
	int GetFaceVertexIndex(int iFaceIndex,int iIndexInFace);
	D3DXMATRIX GetBindPose(int iBoneIndex);
	D3DXMATRIX GetNewPose(int iBoneIndex);
	CHAR* GetBoneName(int iBoneIndex);

	//=======================================================================================
	//�A�j���[�V�����ɕK�v�ȕϐ�
	//=======================================================================================

	//�A�j���[�V����
	std::vector<HlAnimation_Desc*>m_hlAnimationList;					//�A�j���[�V�������i�[���邽�߂̃��X�g

	//���݂̃A�j���[�V�����g���b�N
	DWORD	m_CurrentTrack = 0;											//���݂̃g���b�N

	//1�O�̃A�j���[�V�����g���b�N
	DWORD   m_BeforeTrack = 0;											//�P�܂��̃A�j���[�V�����g���b�N

	//���݂̃A�j���[�V�������J�n����Ă���̎���
	DWORD   m_AnimTime;													//���݂̃A�j���[�V�������J�n���ꂽ����̎���

	//�A�j���[�V�����̃E�F�C�g�������w��
	BOOL AdavancedTime(float time);										//�A�j���[�V�����̃E�F�C�g���Ԃ��w��

	//�A�j���[�V�����X�s�[�h
	//float m_AnimeSpeed = 0.3;
	BOOL m_AnimStopFlg = FALSE;
	void SetStop(bool _flag);

	void Delete();
};

//=======================================================================================
//class CD3DXSKINMESH
//CD3DXSKINMESH �I���W�i�����b�V���N���X
//=======================================================================================
class CD3DXSKINMESH
{
public:
	

	//=======================================================================================
	//�V�F�[�_�[�ɓn���l
	//=======================================================================================
	struct SHADER_SKIN_GLOBAL0
	{
		D3DXVECTOR4 vLightDir;//���C�g����
		D3DXVECTOR4 vEye;//�J�����ʒu
	};

	struct SHADER_SKIN_GLOBAL1
	{
		D3DXMATRIX mW;//���[���h�s��
		D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
		D3DXVECTOR4 vAmbient;//�A���r�G���g��
		D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
		D3DXVECTOR4 vSpecular;//���ʔ���
	};

	struct SHADER_GLOBAL_BONES
	{
		D3DXMATRIX mBone[MAX_BONES];
		SHADER_GLOBAL_BONES()
		{
			for (int i = 0; i<MAX_BONES; i++)
			{
				D3DXMatrixIdentity(&mBone[i]);
			}
		}
	};

	//=======================================================================================
	//�\���̒�`
	//=======================================================================================
	struct LINE_CBUFFER
	{
		D3DXMATRIX mWVP;
		D3DXVECTOR4 Color;
	};
	//=======================================================================================
	//���_�̍\����
	//=======================================================================================
	struct MY_VERTEX
	{
		D3DXVECTOR3 vPos;
		D3DXVECTOR3 vNorm;
		D3DXVECTOR2 vTex;
	};

	struct LINE_VERTEX
	{
		D3DXVECTOR3 vPos;
	};


	//=======================================================================================
	//�����o�ϐ�
	//=======================================================================================
	HWND m_hWnd;	
	//Dx9
	LPDIRECT3D9 m_pD3d9;
	LPDIRECT3DDEVICE9 m_pDevice9;
	//Dx11
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	ID3D11SamplerState* m_pSampleLinear;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Buffer* m_pConstantBuffer0;
	ID3D11Buffer* m_pConstantBuffer1;
	ID3D11Buffer* m_pConstantBufferBone;

	//���b�V��
	D3DXMATRIX m_View;				//�r���[�s��
	D3DXMATRIX m_Proj;				//�v���W�F�N�V�����s��
	D3DXVECTOR3 m_Eye;				//���_
	D3DXPARSER* m_pD3dxMesh;		//�{��
	DWORD m_dwNumVert;				//Vert�̐�
	DWORD m_dwNumFace;				//�ʂ̐�
	DWORD m_dwNumUV;				//UV�̐�
	ID3D11Buffer* m_pVertexBuffer;	//�o�[�e�b�N�X�o�b�t�@�[
	ID3D11Buffer** m_ppIndexBuffer;	//�C���f�b�N�X�o�b�t�@�[
	MY_SKINMATERIAL* m_pMaterial;	//�}�e���A��
	DWORD m_dwNumMaterial;			//�}�e���A���̐�

	D3DXVECTOR3 m_Pos;				//���W
	float m_Yaw;					//Y��
	float m_Pitch;					//X��
	float m_Roll;					//Z��
	D3DXVECTOR3 m_Scale;			//�g��
	D3DXMATRIX m_World;				//���[���h
	D3DXMATRIX m_Rotation;			//��]
	LPD3DXMESH m_pMesh;				//���b�V��
	D3DXVECTOR3 m_Dir;				//����
	D3DXVECTOR3 m_AxisZ;
	D3DXVECTOR3 m_AxisX;
	float m_Radius;

	
	//=======================================================================================
	//���C���������邽�߂̐�
	//=======================================================================================
	ID3D11Buffer* m_pLineVertexBuffer;
	ID3D11Buffer* m_pLineConstantBuffer;
	ID3D11InputLayout* m_pLineVertexLayout;
	ID3D11VertexShader* m_pLineVertexShader;
	ID3D11PixelShader* m_pLinePixelShader;

	//�{�[��
	int m_iNumBone;
	BONE* m_BoneArray;
	
	//=======================================================================================
	//���\�b�h
	//=======================================================================================
	CD3DXSKINMESH();
	~CD3DXSKINMESH();
	HRESULT InitSM(HWND _hWnd,ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext);
	HRESULT CreateIndexBuffer(DWORD dwSize,int* pIndex,ID3D11Buffer** ppIndexBuffer);
	void Render(D3DXMATRIX& , D3DXMATRIX& , D3DXVECTOR3& , D3DXVECTOR3&);
	HRESULT CreateFromX(CHAR* szFileName);
	HRESULT ReadSkinInfo(MY_SKINVERTEX*);
	//void RecursiveSetNewPoseMatrices(BONE* pBone,D3DXMATRIX* pmParent);
	void SetNewPoseMatrices(int frame);
	D3DXMATRIX GetBindPoseMatrix(int index);
	D3DXMATRIX GetCurrentPoseMatrix(int index);
	CHAR* GetBoneNames(int iBoneIndex);

	/**/
	void RenderNoAnim(D3DXMATRIX&);

	//�ύX�������A�j���[�V�����̔ԍ�
	VOID ChangeAnim(DWORD NewAnimNum);

	
	void RenderRay(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vRayDir, float RayLength);
};


