#include "DIRECTOR.h"
#include "DIRECT3D11.h"



void DIRECTOR::Opening()
{

	//=====================================================================
	//�`��
	//=====================================================================
	
	/*FadeIn*/
	//m_pFadeIn->Render(D3DXVECTOR3(0, 0, 0));
	
	/*TitlePlayer*/
	m_pTitlePlayer->Render(D3DXVECTOR3(330, 0, 0),1.4f);

	/*PressEnter���x��*/
	m_pPressEnter->Render(D3DXVECTOR3(250, 350, 0),1.0f);

	/*Exite���x��*/
	m_pExit->Render(D3DXVECTOR3(250, 440, 0),1.0f);


	/*No�^�C�g�����x��*/
	m_pTitle->Render(D3DXVECTOR3(0,0,0),1.0f);

	



	//m_pSound->PlaySound(0, false);

	//=====================================================================
	//�V�[����INIT_STAGE1��
	//=====================================================================

	//Enter�L�[
	if (GetAsyncKeyState(VK_RETURN) && 0x8000)
	{
		m_Scene = INIT_STAGE1;
	}


	
	
}