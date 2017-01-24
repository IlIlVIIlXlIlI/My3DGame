#include "DIRECTOR.h"
#include "DIRECT3D11.h"



void DIRECTOR::Opening()
{

	//=====================================================================
	//描画
	//=====================================================================
	
	/*FadeIn*/
	//m_pFadeIn->Render(D3DXVECTOR3(0, 0, 0));
	
	

	/*PressEnterラベル*/
	//m_pPressEnter->Render(D3DXVECTOR3(250, 350, 0),1.0f);


	
	


	
	//m_pSound->PlaySound(0, false);

	//=====================================================================
	//シーンをINIT_STAGE1へ
	//=====================================================================

	//Enterキー
	if (GetAsyncKeyState(VK_RETURN) && 0x8000)
	{
		m_pNowLod->Render(D3DXVECTOR3((WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 2) + 100, 0), 1.0f);
		m_Scene = INIT_STAGE1;
	}
	else
	{
		/*StartGameラベル*/
		m_pStartGame->Render(D3DXVECTOR3((WINDOW_WIDTH / 8) - 50, (WINDOW_HEIGHT / 2) + 100, 0), 1.0f);

		/*Exiteラベル*/
		m_pExit->Render(D3DXVECTOR3((WINDOW_WIDTH / 8), (WINDOW_HEIGHT / 2) + 150, 0), 1.0f);


		/*Noタイトルラベル*/
		m_pTitle->Render(D3DXVECTOR3((WINDOW_WIDTH / 6), (WINDOW_HEIGHT / 3), 0), 0.6f);


		/*TitlePlayer*/
		m_pTitlePlayer->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) + 120, (WINDOW_HEIGHT / 5) - 10, 0), 0.4f);


	}


	
	
}