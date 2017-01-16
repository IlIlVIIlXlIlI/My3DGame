#include "DIRECTOR.h"
#include "DIRECT3D11.h"



void DIRECTOR::Opening()
{

	//=====================================================================
	//描画
	//=====================================================================
	
	/*FadeIn*/
	//m_pFadeIn->Render(D3DXVECTOR3(0, 0, 0));
	
	/*TitlePlayer*/
	m_pTitlePlayer->Render(D3DXVECTOR3(330, 0, 0),1.4f);

	/*PressEnterラベル*/
	m_pPressEnter->Render(D3DXVECTOR3(250, 350, 0),1.0f);

	/*Exiteラベル*/
	m_pExit->Render(D3DXVECTOR3(250, 440, 0),1.0f);


	/*Noタイトルラベル*/
	m_pTitle->Render(D3DXVECTOR3(0,0,0),1.0f);

	



	//m_pSound->PlaySound(0, false);

	//=====================================================================
	//シーンをINIT_STAGE1へ
	//=====================================================================

	//Enterキー
	if (GetAsyncKeyState(VK_RETURN) && 0x8000)
	{
		m_Scene = INIT_STAGE1;
	}


	
	
}