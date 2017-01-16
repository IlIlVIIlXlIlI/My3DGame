#pragma once

#include<stdio.h>
#include<d3dx9.h>
#include<time.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
#include <Vector>
#include <thread>
#include <atomic>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>
#include <assert.h>
#include "CThread.h"
//必要なライブラリファイルのロード
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")
#pragma comment(lib,"winmm.lib")
//警告非表示
#pragma warning(disable : 4305)
#pragma warning(disable : 4996)
#pragma warning(disable : 4018)
#pragma warning(disable : 4111)
//
//
#define APP_NAME "Forest Escape"
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define ALIGN16 _declspec(align(16))
//
//
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=nullptr; } }
#define MFAIL(code,string) if(FAILED( code ) ) { MessageBox(0,string,"error",MB_OK); return E_FAIL; }
#define MFALSE(code,string) if(!( code ) ) { MessageBox(0,string,"error",MB_OK); return E_FAIL; }
#define MSG(t) MessageBox(0,t,0,MB_OK);

#define PUSH 1		//押されていたら
#define NO_PUSH 0	//離されていたら
//
//
class CELEMENT
{
private:
	

public:
	//=======================================================================================
	//DirectX
	//=======================================================================================
	HWND						m_hWnd;
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pDeviceContext;
	IDXGISwapChain*				m_pSwapChain;
	ID3D11RenderTargetView*		m_pBackBuffer_TexRTV;
	ID3D11DepthStencilView*		m_pBuckBuffer_DSTexDSV;
	ID3D11Texture2D*			m_pBuckBuffer_DSTex;
	ID3D11DepthStencilState*	m_pBuckBuffer_DSTexState;
	ID3D11BlendState*			m_pBlendState;
	ID3D11RasterizerState*		m_pRasterizerState;

	ID3D11InputLayout*			m_pVertexLayout;
	ID3D11VertexShader*			m_pVertexShader;
	ID3D11PixelShader*			m_pPixelShader;
	ID3D11SamplerState*			m_pSampleLinear;

	ID3D11Buffer*				m_pConstantBuffer;		//シェーダの橋渡し用
	ID3D11Buffer*				m_pVertexBuffer;		//バーテックスバッファー

	
protected:
};

//
//プロトタイプ
void InitDirectory(char* root);
void SetRootDirectory();
void SetDataDirectory();
void SetVisualDirectory();
void SetShaderDirectory();
void SetSoundDirectory();