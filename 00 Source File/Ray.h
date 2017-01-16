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


//オリジナル　マテリアル構造体
struct MY_MATERIAL
{
	CHAR szName[110];
	D3DXVECTOR4 Ka;//アンビエント
	D3DXVECTOR4 Kd;//ディフューズ
	D3DXVECTOR4 Ks;//スペキュラー
	CHAR szTextureName[110];//テクスチャーファイル名
	ID3D11ShaderResourceView* pTexture;
	DWORD dwNumFace;//そのマテリアルであるポリゴン数
	MY_MATERIAL()
	{
		ZeroMemory(this, sizeof(MY_MATERIAL));
	}
	~MY_MATERIAL()
	{
		SAFE_RELEASE(pTexture);
	}
};

//頂点の構造体
struct MY_VERTEX
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
	D3DXVECTOR2 vTex;
};

//オリジナルメッシュ
struct MY_MESH
{
	DWORD dwNumVert;
	DWORD dwNumFace;
	DWORD* dwNumFaceInMaterial;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer** ppIndexBuffer;
	int** ppiVertexIndex;
	DWORD m_dwNumMaterial;
	MY_MATERIAL* m_pMaterial;
	D3DXVECTOR3 vPos;
	float scale;//スケール　1.0fが実寸でデフォルト
	D3DXMATRIX mRotation;
	D3DXVECTOR3 vDir;//方向
	MY_VERTEX* pvVertexBuffer;
	MY_MESH()
	{
		ZeroMemory(this, sizeof(MY_MESH));
	}
};

class Ray
{
private:
	
	//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
	struct SIMPLESHADER_CONSTANT_BUFFER0
	{
		D3DXMATRIX mW;//ワールド行列
		D3DXMATRIX mWVP;//ワールドから射影までの変換行列
		D3DXVECTOR4 vLightDir;//ライト方向
		D3DXVECTOR4 vEye;//カメラ位置	
	};

	struct SIMPLESHADER_CONSTANT_BUFFER1
	{
		D3DXVECTOR4 vAmbient;//アンビエント光
		D3DXVECTOR4 vDiffuse;//ディフューズ色
		D3DXVECTOR4 vSpecular;//鏡面反射
		D3DXVECTOR4 vTexture;//テクスチャーが貼られているメッシュかどうかのフラグ
	};

	


	


public:
	Ray();
	~Ray();

	

	HRESULT	 Init(ID3D11DeviceContext*);							//初期化
	HRESULT	 MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);	//シェーダー読み込み

	void RenderMesh(MY_MESH* pMesh);
	void DestroyD3D();
	bool RayHitDetection(D3DXVECTOR3, D3DXVECTOR3, MY_MESH*, float*, D3DXVECTOR3*);
	void CalcPlane(D3DXPLANE* pPlane, D3DXVECTOR3* pvA, D3DXVECTOR3* pvB, D3DXVECTOR3* pvC);
	bool IsInside(D3DXVECTOR3* pvI, D3DXVECTOR3* pvA, D3DXVECTOR3* pvB, D3DXVECTOR3* pvC);
	bool Intersect(D3DXPLANE p, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, float* pfLen);
	D3DXVECTOR3 Slip(D3DXVECTOR3 l, D3DXVECTOR3 n);


	HRESULT InitStaticMesh(LPSTR FileName, MY_MESH* pMesh);
	HRESULT LoadMaterialFromFile(LPSTR FileName, MY_MATERIAL** ppMaterial, DWORD* pdwNUmMaterial);

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	D3DXVECTOR3 m_vEyePt;//視点
	D3DXMATRIX mView;
	D3DXMATRIX mProj;

	//↓モデルの種類ごと(モデルの構造が全て同一ならアプリにひとつ）
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Buffer* m_pConstantBuffer0;
	ID3D11Buffer* m_pConstantBuffer1;
	//↓モデルごと
	MY_MESH m_Mesh[3];
	ID3D11SamplerState* m_pSampleLinear;//テクスチャーのサンプラー






};