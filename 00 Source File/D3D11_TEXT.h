#pragma once

#include "BASE.h"

#define DIMENSION 25.0f
#define TEX_DIMENSION 256.0f

//�e�N�X�`���[�N���X
class D3D11_TEXT : CELEMENT
{
private:
	struct CONSTANT_BUFFER_TEXT
	{
		D3DXMATRIX	mWVP;
		D3DXVECTOR4 vColor;
		D3DXVECTOR4 fAlpha;
	};
	//
	//
	struct SimpleVertex_TEXT
	{
		D3DXVECTOR3 Pos; //�ʒu
		D3DXVECTOR2 vTex; //�e�N�X�`���[���W
	};


	ID3D11BlendState*			m_pBlendState;

	DWORD						m_dwWindowWidth;
	DWORD						m_dwWindowHeight;
	ID3D11ShaderResourceView*	m_pAsciiTexture;
	ID3D11Buffer*				m_pVertexBuffer[100];
	D3DXMATRIX					m_mView;
	D3DXMATRIX					m_mProj;
	float						m_fKerning[100];
	float						m_fScale;//25pixel��� 25pixel=1.0f
	float						m_fAlpha;
	D3DXVECTOR4					m_vColor;


public:
	D3D11_TEXT();
	
	HRESULT Init(ID3D11DeviceContext* pContext,DWORD width,DWORD height,float size,D3DXVECTOR4 vColor);
	void Render(char* text,int x,int y);
	void RenderFont(int FontIndex,int x,int y);

	
	


};