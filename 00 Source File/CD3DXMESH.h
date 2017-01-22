#pragma once
#include "d3d9.h"
#include "BASE.h"
#include "CharacterBase.h"
//レイの長さ
#define RAY_DISTANCE 3

//
//
//あくまでもメッシュデータを”ファイルから取り出す事だけ”が目的。レンダーはDx11のほうで行う。
class CD3DXMESH : public CELEMENT
{
private:

	//=======================================================================================
	//線(ライン)用コンスタントバッファー
	//=======================================================================================
	struct LINE_CBUFFER
	{
		D3DXMATRIX mWVP;
		D3DXVECTOR4 Color;
	};

	//=======================================================================================
	//コンスタントバッファー(Shaderに渡すよう変数)
	//=======================================================================================

	struct SIMPLECONSTANT_BUFFER0
	{
		D3DXMATRIX mW;						//ワールド行列
		D3DXMATRIX mWIT;					//ワールドの逆の転置行列
		D3DXMATRIX mWVP;					//ワールドから射影までの変換行列
		D3DXVECTOR4 vLightDir;				//ライト方向
		D3DXVECTOR4 vEye;					//カメラ位置

	};

	struct SIMPLECONSTANT_BUFFER1
	{
		D3DXVECTOR4 vAmbient;				//アンビエント光
		D3DXVECTOR4 vDiffuse;				//ディフューズ色
		D3DXVECTOR4 vSpecular;				//鏡面反射
	};


	//=======================================================================================
	//オリジナル　マテリアル構造体
	//=======================================================================================
	struct MY_MATERIAL
	{
		CHAR			szName[110];					//名前
		D3DXVECTOR4		Ambient;						//アンビエント
		D3DXVECTOR4		Diffuse;						//ディフューズ
		D3DXVECTOR4		Specular;						//スペキュラー
		CHAR			szTextureName[110];				//テクスチャーファイル名
		ID3D11ShaderResourceView* pTexture;				//テクスチャの設定
		DWORD			dwNumFace;						//そのマテリアルであるポリゴン数
		MY_MATERIAL()
		{
			ZeroMemory(this, sizeof(MY_MATERIAL));
		}
		~MY_MATERIAL()
		{
			SAFE_RELEASE(pTexture);
		}
	};
	//=======================================================================================
	//頂点の構造体
	//=======================================================================================
	struct MY_VERTEX
	{
		D3DXVECTOR3 vPos;								//座標
		D3DXVECTOR3 vNorm;								//法線
		D3DXVECTOR2 vTex;								//テクスチャ
		D3DXVECTOR4 vTangent;							//接線の成分が必要
	};

	//=======================================================================================
	//接線成分の無い頂点構造体（Xファイル内の頂点フォーマット。読み込む際に便利なので定義する）
	//=======================================================================================
	struct X_VERTEX
	{
		D3DXVECTOR3 vPos;								//座標
		D3DXVECTOR3 vNorm;								//法線
		D3DXVECTOR2 vTex;								//テクスチャ
	};

	//=======================================================================================
	//ライン用構造体
	//=======================================================================================
	struct LINE_VERTEX
	{
		D3DXVECTOR3 vPos;								//座標
	};

	//=======================================================================================
	//スフィア構造体
	//=======================================================================================
	struct SPHERE
	{
		D3DXVECTOR3 Center;
		float Radius;
	};


	//=======================================================================================
	//Data
	//=======================================================================================
	HWND					m_hWnd;						//ウィンドウ	
	DWORD					m_dwNumMaterial;			//マテリアル

	//=======================================================================================
	//Dx9(Xファイルの読み込みをするため)
	//=======================================================================================
	LPDIRECT3D9				m_pD3d9;					//デバイス　
	LPDIRECT3DDEVICE9		m_pDevice9;					//デバイス
	D3DMATERIAL9*			pMeshMaterials;				//マテリアル
	DWORD					m_NumAttr;					//数
	DWORD					m_AttrID[300];				//300属性まで
	bool					m_Tex;						//テクスチャー

	//=======================================================================================
	//Dx11
	//=======================================================================================
	ID3D11Device*			m_pDevice11;				//デバイス
	ID3D11DeviceContext*	m_pDeviceContext11;			//デバイスコンテキスト
	ID3D11Buffer*			m_pConstantBuffer0;			//バッファー0
	ID3D11Buffer*			m_pConstantBuffer1;			//バッファー1
	ID3D11Buffer*			m_pVertexBuffer;			//バーテックスバッファー
	ID3D11Buffer**			m_ppIndexBuffer;			//インデックスバッファー

	//=======================================================================================
	/*Ray可視化のための変数*/
	//=======================================================================================
	ID3D11Buffer*			m_pLineVertexBuffer;		//ライン用バッファー
	ID3D11Buffer*			m_pLineConstantBuffer;		//ライン用のコンスタントバッファー
	ID3D11InputLayout*		m_pLineVertexLayout;		//ライン用の頂点レイアウト
	ID3D11VertexShader*		m_pLineVertexShader;		//ライン用の頂点シェーダー
	ID3D11PixelShader*		m_pLinePixelShader;			//ライン用のピクセルシェーダー

	//=======================================================================================
	//ライト情報&テクスチャ&サンプラー
	//=======================================================================================
	float					m_fIntensity;				//ライト情報
	char					m_TextureFileName[20][256]; //テクスチャーファイル名（８枚まで）
	ID3D11SamplerState*		m_pSampleLinear;			//テクスチャーのサンプラー
	MY_MATERIAL*			m_pMaterial;				//マテリアル
	bool					m_Texture;					//テクスチャ
	ID3D11ShaderResourceView* m_pNormalTexture;			//ノーマルマップ用　テクスチャー


	//=======================================================================================
	//ShadowMap
	//=======================================================================================
	//ID3D11VertexShader*		m_pDepthVertexShader;		//深度テクスチャーレンダリング用
	//ID3D11PixelShader*		m_pDepthPixelShader;		//深度テクスチャーレンダリング用

	//ID3D11RenderTargetView*	m_pBackBuffer_TexRTV;		//バックバッファーのRTV;
	//ID3D11Texture2D*		m_pBackBuffer_DSTex;			//バックバッファー用のDS
	//ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;		//バックバッファー用のDSのDSV

	//ID3D11Texture2D*		m_pDepthMap_Tex;				//深度マップテクスチャー
	//ID3D11RenderTargetView* m_pDepthMap_Tex;				//深度マップテクスチャーのRTV
	//ID3D11ShaderResourceView* m_pDepthMap_TexSRV;			//深度マップテクスチャーのSRV
	//ID3D11Texture2D*		m_mDepthMap_DSTex;				//深度マップテクスチャー用DS
	//ID3D11DepthStencilView* m_pDepthMap_DSTexDSC;			//深度マップテクスチャー用のDSV


	//=======================================================================================
	//resource
	//=======================================================================================

	/*DirectX9の初期化*/
	HRESULT InitDx9();

	/*シェーダーの初期化*/
	HRESULT InitShader();

	/*Xファイルのロード*/
	HRESULT LoadXMesh(LPSTR FileName);

	/*ノーマルマップのロード*/
	HRESULT LoadNomalMap(LPSTR, ID3D11ShaderResourceView*);

public:

	//=======================================================================================
	//Method
	//=======================================================================================
	CD3DXMESH();
	CD3DXMESH(HWND _hWnd, ID3D11Device* _pDevice11, ID3D11DeviceContext* _pContext11, LPSTR _FileName);
	~CD3DXMESH();

	//=======================================================================================
	//ポジション&拡大&方向
	//=======================================================================================
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_Pos;
	float m_fYaw, m_fPitch, m_fRoll;
	float m_fScale;
	float m_Radius;



	//=======================================================================================
	//初期化
	//=======================================================================================

	/*初期化*/
	HRESULT	Init(HWND hWnd, ID3D11Device*, ID3D11DeviceContext*, LPSTR);

	HRESULT Init(HWND _hWnd, ID3D11Device* _pDevice11, ID3D11DeviceContext* _pContext11,
		LPSTR _FileName, LPSTR _NomalMap);

	//=======================================================================================
	//レンダー(描画)
	//=======================================================================================

	/*レンダー(描画)*/
	void	Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vEye);


	//=======================================================================================
	//カリング
	//=======================================================================================

	/*カリング*/
	bool	VFCulling(CD3DXMESH*, D3DXMATRIX*, float, float, float, float);

	//=======================================================================================
	//ノーマルマップのセット
	//=======================================================================================

	void SetNomalMap(ID3D11ShaderResourceView*);

	//=======================================================================================
	//変換行列
	//=======================================================================================
	D3DXMATRIX	mWorld, mTran, mYaw, mPitch, mRoll, mScale;		//各行列
	D3DXVECTOR3 ToVec;											//方向ベクトル
	D3DXMATRIX	mCRot;											//カメラの角度
	D3DXMATRIX	mTmp;											//方向に近い方から回転する
	D3DXMATRIX	mRot;											//角度
	/*追加============================================*/
	//レイの可視化 本来ならいらない
	void RenderRay(D3DXMATRIX& mView, D3DXMATRIX& mProj,
		D3DXVECTOR3& vRayDir, float RayLength);
	//=================================================

	D3DXMATRIX GetWorld() 
	{
		return mWorld;
	}


	//D3DXMATRIX m_World;
	D3DXVECTOR3 m_Dir;
	LPD3DXMESH pMesh;

	SPHERE m_Sphere;
};