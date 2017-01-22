#pragma once
#include "d3d9.h"
#include "BASE.h"
#include "CharacterBase.h"
//���C�̒���
#define RAY_DISTANCE 3

//
//
//�����܂ł����b�V���f�[�^���h�t�@�C��������o���������h���ړI�B�����_�[��Dx11�̂ق��ōs���B
class CD3DXMESH : public CELEMENT
{
private:

	//=======================================================================================
	//��(���C��)�p�R���X�^���g�o�b�t�@�[
	//=======================================================================================
	struct LINE_CBUFFER
	{
		D3DXMATRIX mWVP;
		D3DXVECTOR4 Color;
	};

	//=======================================================================================
	//�R���X�^���g�o�b�t�@�[(Shader�ɓn���悤�ϐ�)
	//=======================================================================================

	struct SIMPLECONSTANT_BUFFER0
	{
		D3DXMATRIX mW;						//���[���h�s��
		D3DXMATRIX mWIT;					//���[���h�̋t�̓]�u�s��
		D3DXMATRIX mWVP;					//���[���h����ˉe�܂ł̕ϊ��s��
		D3DXVECTOR4 vLightDir;				//���C�g����
		D3DXVECTOR4 vEye;					//�J�����ʒu

	};

	struct SIMPLECONSTANT_BUFFER1
	{
		D3DXVECTOR4 vAmbient;				//�A���r�G���g��
		D3DXVECTOR4 vDiffuse;				//�f�B�t���[�Y�F
		D3DXVECTOR4 vSpecular;				//���ʔ���
	};


	//=======================================================================================
	//�I���W�i���@�}�e���A���\����
	//=======================================================================================
	struct MY_MATERIAL
	{
		CHAR			szName[110];					//���O
		D3DXVECTOR4		Ambient;						//�A���r�G���g
		D3DXVECTOR4		Diffuse;						//�f�B�t���[�Y
		D3DXVECTOR4		Specular;						//�X�y�L�����[
		CHAR			szTextureName[110];				//�e�N�X�`���[�t�@�C����
		ID3D11ShaderResourceView* pTexture;				//�e�N�X�`���̐ݒ�
		DWORD			dwNumFace;						//���̃}�e���A���ł���|���S����
		MY_MATERIAL()
		{
			ZeroMemory(this, sizeof(MY_MATERIAL));
		}
		~MY_MATERIAL()
		{
			SAFE_RELEASE(pTexture);
		}
	};
	//=======================================================================================
	//���_�̍\����
	//=======================================================================================
	struct MY_VERTEX
	{
		D3DXVECTOR3 vPos;								//���W
		D3DXVECTOR3 vNorm;								//�@��
		D3DXVECTOR2 vTex;								//�e�N�X�`��
		D3DXVECTOR4 vTangent;							//�ڐ��̐������K�v
	};

	//=======================================================================================
	//�ڐ������̖������_�\���́iX�t�@�C�����̒��_�t�H�[�}�b�g�B�ǂݍ��ލۂɕ֗��Ȃ̂Œ�`����j
	//=======================================================================================
	struct X_VERTEX
	{
		D3DXVECTOR3 vPos;								//���W
		D3DXVECTOR3 vNorm;								//�@��
		D3DXVECTOR2 vTex;								//�e�N�X�`��
	};

	//=======================================================================================
	//���C���p�\����
	//=======================================================================================
	struct LINE_VERTEX
	{
		D3DXVECTOR3 vPos;								//���W
	};

	//=======================================================================================
	//�X�t�B�A�\����
	//=======================================================================================
	struct SPHERE
	{
		D3DXVECTOR3 Center;
		float Radius;
	};


	//=======================================================================================
	//Data
	//=======================================================================================
	HWND					m_hWnd;						//�E�B���h�E	
	DWORD					m_dwNumMaterial;			//�}�e���A��

	//=======================================================================================
	//Dx9(X�t�@�C���̓ǂݍ��݂����邽��)
	//=======================================================================================
	LPDIRECT3D9				m_pD3d9;					//�f�o�C�X�@
	LPDIRECT3DDEVICE9		m_pDevice9;					//�f�o�C�X
	D3DMATERIAL9*			pMeshMaterials;				//�}�e���A��
	DWORD					m_NumAttr;					//��
	DWORD					m_AttrID[300];				//300�����܂�
	bool					m_Tex;						//�e�N�X�`���[

	//=======================================================================================
	//Dx11
	//=======================================================================================
	ID3D11Device*			m_pDevice11;				//�f�o�C�X
	ID3D11DeviceContext*	m_pDeviceContext11;			//�f�o�C�X�R���e�L�X�g
	ID3D11Buffer*			m_pConstantBuffer0;			//�o�b�t�@�[0
	ID3D11Buffer*			m_pConstantBuffer1;			//�o�b�t�@�[1
	ID3D11Buffer*			m_pVertexBuffer;			//�o�[�e�b�N�X�o�b�t�@�[
	ID3D11Buffer**			m_ppIndexBuffer;			//�C���f�b�N�X�o�b�t�@�[

	//=======================================================================================
	/*Ray�����̂��߂̕ϐ�*/
	//=======================================================================================
	ID3D11Buffer*			m_pLineVertexBuffer;		//���C���p�o�b�t�@�[
	ID3D11Buffer*			m_pLineConstantBuffer;		//���C���p�̃R���X�^���g�o�b�t�@�[
	ID3D11InputLayout*		m_pLineVertexLayout;		//���C���p�̒��_���C�A�E�g
	ID3D11VertexShader*		m_pLineVertexShader;		//���C���p�̒��_�V�F�[�_�[
	ID3D11PixelShader*		m_pLinePixelShader;			//���C���p�̃s�N�Z���V�F�[�_�[

	//=======================================================================================
	//���C�g���&�e�N�X�`��&�T���v���[
	//=======================================================================================
	float					m_fIntensity;				//���C�g���
	char					m_TextureFileName[20][256]; //�e�N�X�`���[�t�@�C�����i�W���܂Łj
	ID3D11SamplerState*		m_pSampleLinear;			//�e�N�X�`���[�̃T���v���[
	MY_MATERIAL*			m_pMaterial;				//�}�e���A��
	bool					m_Texture;					//�e�N�X�`��
	ID3D11ShaderResourceView* m_pNormalTexture;			//�m�[�}���}�b�v�p�@�e�N�X�`���[


	//=======================================================================================
	//ShadowMap
	//=======================================================================================
	//ID3D11VertexShader*		m_pDepthVertexShader;		//�[�x�e�N�X�`���[�����_�����O�p
	//ID3D11PixelShader*		m_pDepthPixelShader;		//�[�x�e�N�X�`���[�����_�����O�p

	//ID3D11RenderTargetView*	m_pBackBuffer_TexRTV;		//�o�b�N�o�b�t�@�[��RTV;
	//ID3D11Texture2D*		m_pBackBuffer_DSTex;			//�o�b�N�o�b�t�@�[�p��DS
	//ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;		//�o�b�N�o�b�t�@�[�p��DS��DSV

	//ID3D11Texture2D*		m_pDepthMap_Tex;				//�[�x�}�b�v�e�N�X�`���[
	//ID3D11RenderTargetView* m_pDepthMap_Tex;				//�[�x�}�b�v�e�N�X�`���[��RTV
	//ID3D11ShaderResourceView* m_pDepthMap_TexSRV;			//�[�x�}�b�v�e�N�X�`���[��SRV
	//ID3D11Texture2D*		m_mDepthMap_DSTex;				//�[�x�}�b�v�e�N�X�`���[�pDS
	//ID3D11DepthStencilView* m_pDepthMap_DSTexDSC;			//�[�x�}�b�v�e�N�X�`���[�p��DSV


	//=======================================================================================
	//resource
	//=======================================================================================

	/*DirectX9�̏�����*/
	HRESULT InitDx9();

	/*�V�F�[�_�[�̏�����*/
	HRESULT InitShader();

	/*X�t�@�C���̃��[�h*/
	HRESULT LoadXMesh(LPSTR FileName);

	/*�m�[�}���}�b�v�̃��[�h*/
	HRESULT LoadNomalMap(LPSTR, ID3D11ShaderResourceView*);

public:

	//=======================================================================================
	//Method
	//=======================================================================================
	CD3DXMESH();
	CD3DXMESH(HWND _hWnd, ID3D11Device* _pDevice11, ID3D11DeviceContext* _pContext11, LPSTR _FileName);
	~CD3DXMESH();

	//=======================================================================================
	//�|�W�V����&�g��&����
	//=======================================================================================
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_Pos;
	float m_fYaw, m_fPitch, m_fRoll;
	float m_fScale;
	float m_Radius;



	//=======================================================================================
	//������
	//=======================================================================================

	/*������*/
	HRESULT	Init(HWND hWnd, ID3D11Device*, ID3D11DeviceContext*, LPSTR);

	HRESULT Init(HWND _hWnd, ID3D11Device* _pDevice11, ID3D11DeviceContext* _pContext11,
		LPSTR _FileName, LPSTR _NomalMap);

	//=======================================================================================
	//�����_�[(�`��)
	//=======================================================================================

	/*�����_�[(�`��)*/
	void	Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vEye);


	//=======================================================================================
	//�J�����O
	//=======================================================================================

	/*�J�����O*/
	bool	VFCulling(CD3DXMESH*, D3DXMATRIX*, float, float, float, float);

	//=======================================================================================
	//�m�[�}���}�b�v�̃Z�b�g
	//=======================================================================================

	void SetNomalMap(ID3D11ShaderResourceView*);

	//=======================================================================================
	//�ϊ��s��
	//=======================================================================================
	D3DXMATRIX	mWorld, mTran, mYaw, mPitch, mRoll, mScale;		//�e�s��
	D3DXVECTOR3 ToVec;											//�����x�N�g��
	D3DXMATRIX	mCRot;											//�J�����̊p�x
	D3DXMATRIX	mTmp;											//�����ɋ߂��������]����
	D3DXMATRIX	mRot;											//�p�x
	/*�ǉ�============================================*/
	//���C�̉��� �{���Ȃ炢��Ȃ�
	void RenderRay(D3DXMATRIX& mView, D3DXMATRIX& mProj,
		D3DXVECTOR3& vRayDir, float RayLength);
	//=================================================

	D3DXMATRIX GetWorld() 
	{
		return mWorld;
	}


	//D3DXMATRIX m_World;
	D3DXVECTOR3 m_Dir;
	LPD3DXMESH pMesh;

	SPHERE m_Sphere;
};