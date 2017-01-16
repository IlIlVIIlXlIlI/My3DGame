#pragma once
//ヘッダーファイルのインクルード
#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
//必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")
//警告非表示
#pragma warning(disable : 4305)
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}

class PARTICLE
{
private:

	//頂点の構造体
	struct PARTICLE_Vertex
	{
		D3DXVECTOR3 Pos; //位置
	};
	
	struct PARTICLE_CONSTANT_BUFFER
	{
		D3DXMATRIX mWVP;
	};


	struct PART
	{
		/*パーティクル本体の構造体*/
		D3DXVECTOR3			 Pos;
		D3DXVECTOR3			 Dir;
		float				 Speed;
		int					 BirthFrame;

		PART()
		{
			ZeroMemory(this, sizeof(PART));
		}
	};


	/*DirectX11のメンバ変数*/
	ID3D11Device*				m_pDevice;				//作成の主力
	ID3D11DeviceContext*		m_pDeviceContext;		//描画の主力
	ID3D11VertexShader*			m_pVertexShader;		//バーテックスシェーダー用
	ID3D11GeometryShader*		m_pGeometryShader;		//ジオメトリシェーダ
	ID3D11PixelShader*			m_pPixelShader;			//ピクセルシェーダー用
	ID3D11InputLayout*			m_pVertexLayout;		//頂点インプットレイアウト用

	ID3D11Buffer*				m_pConstantBuffer;		//シェーダの橋渡し用
	ID3D11Buffer*				m_pVertexBuffer;		//バーテックスバッファー


	ID3D11SamplerState*			m_pSampler;				//テクスチャーのサンプラー
	ID3D11ShaderResourceView*	m_pTexture;				//テクスチャー本体



	/*パーティクル関係のメンバ変数*/
	int						m_MaxParticle;
	D3DXVECTOR3				m_EmitPos;
	PART*					pPartArray;
	int						m_Frame;

	PARTICLE*				m_pParticle;

public:
	/*パーティクルのメンバ関数*/
	PARTICLE();
	PARTICLE(int MaxParticle, D3DXVECTOR3& EmitPos);
	~PARTICLE();
	void Run();
	D3DXVECTOR3& GetParticlePos(int Index);

	HRESULT	 Init(ID3D11DeviceContext*);							//初期化
	HRESULT	 MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);	//シェーダー読み込み
	HRESULT  InitModel();											//メッシュの初期化
	void	 Render();												//描画関数
	void	 DestroyD3D();											//Release関数


};