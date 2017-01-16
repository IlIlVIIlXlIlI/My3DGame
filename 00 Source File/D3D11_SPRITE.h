#pragma once

#include "BASE.h"

class SPRITE : public CELEMENT
{
/*スプライト　クラス*/
private:

	/*頂点の構造体*/
	struct SpriteVertex
	{
		D3DXVECTOR3 Pos;					//位置
		D3DXVECTOR2 UV;						//テクスチャー座標
	};

	/*スプライト用のコンスタントバッファー*/
	struct SPRITE_CONSTANT_BUFFER
	{
		ALIGN16 D3DXMATRIX mW;				//ワールド座標
		ALIGN16 float ViewPortWidth;		//ビューポート横幅
		ALIGN16 float ViewPortHeight;		//ビューポート縦幅
	};

	ID3D11SamplerState*			m_pSampler;	//テクスチャーのサンプラー
	ID3D11ShaderResourceView*	m_pTexture;	//テクスチャー本体
	
	
	D3DXMATRIX					mTran;		//移動行列
	D3DXMATRIX					mScale;		//拡大行列
	D3DXMATRIX					mRot;		//回転行列
public:
	/*コンストラクタ*/
	SPRITE();
	SPRITE(ID3D11DeviceContext* _pContext, LPSTR _texName, const int _WIN_WIDTH, const int _WIN_HEIGHT);

	D3DXVECTOR3					m_Pos;		//ポジション
	D3DXVECTOR3					m_Scale;	//拡大
	float						m_Rot;		//回転

	/*スプライトの初期化*/
	HRESULT	 Init(ID3D11DeviceContext* _pContext, LPSTR _texName,
		const int _WIN_WIDTH, const int _WIN_HEIGHT);					//初期化

	/*シェーダーの初期化*/
	HRESULT	 MakeShader(LPSTR, LPSTR, LPSTR, void**, ID3DBlob**);		//シェーダー読み込み

	/*板ポリを作る*/
	HRESULT  InitModel(const int,const int);							//メッシュの初期化

	/*描画*/
	void	 Render(D3DXVECTOR3, float);							//描画関数

	/*Release*/
	void	 DestroyD3D();												//Release関数


};