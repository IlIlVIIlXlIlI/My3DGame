#include <stdio.h>
#include <windows.h>
#include<d3dx9.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
#include "BASE.h"

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//コンピュートシェーダーへのデータ受け渡し用の構造体を定義
struct MY_DATA
{
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2;
	D3DXVECTOR3 v3;
	float fLength;
	bool Hit;
};
//コンスタントバッファーのアプリ側定義
struct CBUFFER
{
	D3DXVECTOR4 vStart;
	D3DXVECTOR4 vEnd;
};

class COMPUTE_RAY
{
private:


public:
	COMPUTE_RAY();
	~COMPUTE_RAY();



};