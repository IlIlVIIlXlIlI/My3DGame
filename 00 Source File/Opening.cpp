#include "DIRECTOR.h"
#include "DIRECT3D11.h"



void DIRECTOR::Opening()
{

	//=====================================================================
	//�`��
	//=====================================================================
	
	/*FadeIn*/
	//m_pFadeIn->Render(D3DXVECTOR3(0, 0, 0));
	
	

	/*PressEnter���x��*/
	//m_pPressEnter->Render(D3DXVECTOR3(250, 350, 0),1.0f);


	
	


	
	//m_pSound->PlaySound(0, false);

	//=====================================================================
	//�V�[����INIT_STAGE1��
	//=====================================================================

	//Enter�L�[
	if (GetAsyncKeyState(VK_RETURN) && 0x8000)
	{
		m_pNowLod->Render(D3DXVECTOR3((WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 2) + 100, 0), 1.0f);
		m_Scene = INIT_STAGE1;
	}
	else
	{
		/*StartGame���x��*/
		m_pStartGame->Render(D3DXVECTOR3((WINDOW_WIDTH / 8) - 50, (WINDOW_HEIGHT / 2) + 100, 0), 1.0f);

		/*Exite���x��*/
		m_pExit->Render(D3DXVECTOR3((WINDOW_WIDTH / 8), (WINDOW_HEIGHT / 2) + 150, 0), 1.0f);


		/*No�^�C�g�����x��*/
		m_pTitle->Render(D3DXVECTOR3((WINDOW_WIDTH / 6), (WINDOW_HEIGHT / 3), 0), 0.6f);


		/*TitlePlayer*/
		m_pTitlePlayer->Render(D3DXVECTOR3((WINDOW_WIDTH / 2) + 120, (WINDOW_HEIGHT / 5) - 10, 0), 0.4f);


	}


	
	
}