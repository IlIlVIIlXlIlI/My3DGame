#pragma once
//�w�b�_�[�t�@�C���̃C���N���[�h
#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
//�K�v�ȃ��C�u�����t�@�C���̃��[�h
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")
//�x����\��
#pragma warning(disable : 4305)
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}

class PARTICLE
{
private:

	//���_�̍\����
	struct PARTICLE_Vertex
	{
		D3DXVECTOR3 Pos; //�ʒu
	};
	
	struct PARTICLE_CONSTANT_BUFFER
	{
		D3DXMATRIX mWVP;
	};


	struct PART
	{
		/*�p�[�e�B�N���{�̂̍\����*/
		D3DXVECTOR3			 Pos;
		D3DXVECTOR3			 Dir;
		float				 Speed;
		int					 BirthFrame;

		PART()
		{
			ZeroMemory(this, sizeof(PART));
		}
	};


	/*DirectX11�̃����o�ϐ�*/
	ID3D11Device*				m_pDevice;				//�쐬�̎��
	ID3D11DeviceContext*		m_pDeviceContext;		//�`��̎��
	ID3D11VertexShader*			m_pVertexShader;		//�o�[�e�b�N�X�V�F�[�_�[�p
	ID3D11GeometryShader*		m_pGeometryShader;		//�W�I���g���V�F�[�_
	ID3D11PixelShader*			m_pPixelShader;			//�s�N�Z���V�F�[�_�[�p
	ID3D11InputLayout*			m_pVertexLayout;		//���_�C���v�b�g���C�A�E�g�p

	ID3D11Buffer*				m_pConstantBuffer;		//�V�F�[�_�̋��n���p
	ID3D11Buffer*				m_pVertexBuffer;		//�o�[�e�b�N�X�o�b�t�@�[


	ID3D11SamplerState*			m_pSampler;				//�e�N�X�`���[�̃T���v���[
	ID3D11ShaderResourceView*	m_pTexture;				//�e�N�X�`���[�{��



	/*�p�[�e�B�N���֌W�̃����o�ϐ�*/
	int						m_MaxParticle;
	D3DXVECTOR3				m_EmitPos;
	PART*					pPartArray;
	int						m_Frame;

	PARTICLE*				m_pParticle;

public:
	/*�p�[�e�B�N���̃����o�֐�*/
	PARTICLE();
	PARTICLE(int MaxParticle, D3DXVECTOR3& EmitPos);
	~PARTICLE();
	void Run();
	D3DXVECTOR3& GetParticlePos(int Index);

	HRESULT	 Init(ID3D11DeviceContext*);							//������
	HRESULT	 MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);	//�V�F�[�_�[�ǂݍ���
	HRESULT  InitModel();											//���b�V���̏�����
	void	 Render();												//�`��֐�
	void	 DestroyD3D();											//Release�֐�


};