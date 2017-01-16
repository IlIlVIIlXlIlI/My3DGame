#include "WINDOW.h"

WINDOW* g_pWindow=nullptr;
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
//
//
//
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return g_pWindow->MsgProc(hWnd,uMsg,wParam,lParam);
}
//
//======================================================================================
//ウィンドウの初期化
//======================================================================================
HRESULT WINDOW::InitWindow(HINSTANCE hInstance,
		INT iX,INT iY,INT iWidth,INT iHeight,LPSTR WindowName)
{
	g_pWindow=this;
	// ウィンドウの定義
	WNDCLASSEX wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(nullptr,IDI_APPLICATION);
	RegisterClassEx(&wc);
	//ウィンドウの作成
	m_hWnd=CreateWindow(WindowName,WindowName,WS_OVERLAPPEDWINDOW,
		0,0,iWidth,iHeight,0,0,hInstance,0);
	if(!m_hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);
	
	return S_OK;
}
//
//======================================================================================
//メッセージプロック
//======================================================================================
 LRESULT WINDOW::MsgProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	switch(iMsg)
	{
		case WM_KEYDOWN:
		switch((char)wParam)
		{
			case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
		case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc (hWnd, iMsg, wParam, lParam);
}