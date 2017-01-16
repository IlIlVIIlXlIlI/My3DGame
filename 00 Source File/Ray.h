#include <stdio.h>
#include <windows.h>
#include<d3dx9.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
#include "BASE.h"

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")


//�I���W�i���@�}�e���A���\����
struct MY_MATERIAL
{
	CHAR szName[110];
	D3DXVECTOR4 Ka;//�A���r�G���g
	D3DXVECTOR4 Kd;//�f�B�t���[�Y
	D3DXVECTOR4 Ks;//�X�y�L�����[
	CHAR szTextureName[110];//�e�N�X�`���[�t�@�C����
	ID3D11ShaderResourceView* pTexture;
	DWORD dwNumFace;//���̃}�e���A���ł���|���S����
	MY_MATERIAL()
	{
		ZeroMemory(this, sizeof(MY_MATERIAL));
	}
	~MY_MATERIAL()
	{
		SAFE_RELEASE(pTexture);
	}
};

//���_�̍\����
struct MY_VERTEX
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
	D3DXVECTOR2 vTex;
};

//�I���W�i�����b�V��
struct MY_MESH
{
	DWORD dwNumVert;
	DWORD dwNumFace;
	DWORD* dwNumFaceInMaterial;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer** ppIndexBuffer;
	int** ppiVertexIndex;
	DWORD m_dwNumMaterial;
	MY_MATERIAL* m_pMaterial;
	D3DXVECTOR3 vPos;
	float scale;//�X�P�[���@1.0f�������Ńf�t�H���g
	D3DXMATRIX mRotation;
	D3DXVECTOR3 vDir;//����
	MY_VERTEX* pvVertexBuffer;
	MY_MESH()
	{
		ZeroMemory(this, sizeof(MY_MESH));
	}
};

class Ray
{
private:
	
	//Simple�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
	struct SIMPLESHADER_CONSTANT_BUFFER0
	{
		D3DXMATRIX mW;//���[���h�s��
		D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
		D3DXVECTOR4 vLightDir;//���C�g����
		D3DXVECTOR4 vEye;//�J�����ʒu	
	};

	struct SIMPLESHADER_CONSTANT_BUFFER1
	{
		D3DXVECTOR4 vAmbient;//�A���r�G���g��
		D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
		D3DXVECTOR4 vSpecular;//���ʔ���
		D3DXVECTOR4 vTexture;//�e�N�X�`���[���\���Ă��郁�b�V�����ǂ����̃t���O
	};

	


	


public:
	Ray();
	~Ray();

	

	HRESULT	 Init(ID3D11DeviceContext*);							//������
	HRESULT	 MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);	//�V�F�[�_�[�ǂݍ���

	void RenderMesh(MY_MESH* pMesh);
	void DestroyD3D();
	bool RayHitDetection(D3DXVECTOR3, D3DXVECTOR3, MY_MESH*, float*, D3DXVECTOR3*);
	void CalcPlane(D3DXPLANE* pPlane, D3DXVECTOR3* pvA, D3DXVECTOR3* pvB, D3DXVECTOR3* pvC);
	bool IsInside(D3DXVECTOR3* pvI, D3DXVECTOR3* pvA, D3DXVECTOR3* pvB, D3DXVECTOR3* pvC);
	bool Intersect(D3DXPLANE p, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, float* pfLen);
	D3DXVECTOR3 Slip(D3DXVECTOR3 l, D3DXVECTOR3 n);


	HRESULT InitStaticMesh(LPSTR FileName, MY_MESH* pMesh);
	HRESULT LoadMaterialFromFile(LPSTR FileName, MY_MATERIAL** ppMaterial, DWORD* pdwNUmMaterial);

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	D3DXVECTOR3 m_vEyePt;//���_
	D3DXMATRIX mView;
	D3DXMATRIX mProj;

	//�����f���̎�ނ���(���f���̍\�����S�ē���Ȃ�A�v���ɂЂƂj
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Buffer* m_pConstantBuffer0;
	ID3D11Buffer* m_pConstantBuffer1;
	//�����f������
	MY_MESH m_Mesh[3];
	ID3D11SamplerState* m_pSampleLinear;//�e�N�X�`���[�̃T���v���[






};