#pragma once
#include "BASE.h"
#include "WINDOW.h"
#include "D3D11_TEXT.h"
//


#define SAMPLE_COUNT 4
#define SAMPLE_QUALITY 0.5

struct D3D_INIT
{
	HWND hWnd;
};
//
//
class DIRECT3D11 : public CELEMENT
{
public:
	//=======================================================================================
	//Data
	//=======================================================================================
	HWND			 m_hWnd;

#ifdef _DEBUG
	D3D11_TEXT*		 m_pText;
#endif // DEBUG

	

	//=======================================================================================
	//Method
	//=======================================================================================
	DIRECT3D11();
	~DIRECT3D11();

	HRESULT Init(D3D_INIT*);
	void	ShowFPS();
	void	Clear();
	HRESULT Present();
	
};
