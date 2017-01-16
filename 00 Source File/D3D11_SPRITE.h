#pragma once

#include "BASE.h"

class SPRITE : public CELEMENT
{
/*�X�v���C�g�@�N���X*/
private:

	/*���_�̍\����*/
	struct SpriteVertex
	{
		D3DXVECTOR3 Pos;					//�ʒu
		D3DXVECTOR2 UV;						//�e�N�X�`���[���W
	};

	/*�X�v���C�g�p�̃R���X�^���g�o�b�t�@�[*/
	struct SPRITE_CONSTANT_BUFFER
	{
		ALIGN16 D3DXMATRIX mW;				//���[���h���W
		ALIGN16 float ViewPortWidth;		//�r���[�|�[�g����
		ALIGN16 float ViewPortHeight;		//�r���[�|�[�g�c��
	};

	ID3D11SamplerState*			m_pSampler;	//�e�N�X�`���[�̃T���v���[
	ID3D11ShaderResourceView*	m_pTexture;	//�e�N�X�`���[�{��
	
	
	D3DXMATRIX					mTran;		//�ړ��s��
	D3DXMATRIX					mScale;		//�g��s��
	D3DXMATRIX					mRot;		//��]�s��
public:
	/*�R���X�g���N�^*/
	SPRITE();
	SPRITE(ID3D11DeviceContext* _pContext, LPSTR _texName, const int _WIN_WIDTH, const int _WIN_HEIGHT);

	D3DXVECTOR3					m_Pos;		//�|�W�V����
	D3DXVECTOR3					m_Scale;	//�g��
	float						m_Rot;		//��]

	/*�X�v���C�g�̏�����*/
	HRESULT	 Init(ID3D11DeviceContext* _pContext, LPSTR _texName,
		const int _WIN_WIDTH, const int _WIN_HEIGHT);					//������

	/*�V�F�[�_�[�̏�����*/
	HRESULT	 MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);		//�V�F�[�_�[�ǂݍ���

	/*�|�������*/
	HRESULT  InitModel(const int,const int);							//���b�V���̏�����

	/*�`��*/
	void	 Render(D3DXVECTOR3, float);							//�`��֐�

	/*Release*/
	void	 DestroyD3D();												//Release�֐�


};