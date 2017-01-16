#pragma once
#include "BASE.h"


#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define MAX_BONES 255

//=======================================================================================
//マクロ
//=======================================================================================
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=nullptr; } }
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }

//=======================================================================================
//X読み込み関数の参照
//=======================================================================================
HRESULT InitX(CHAR* szFileName);
void DestroyX();



//=======================================================================================
//オリジナル　マテリアル構造体
//=======================================================================================
struct MY_SKINMATERIAL
{
	CHAR szName[110];
	D3DXVECTOR4 Ka;//アンビエント
	D3DXVECTOR4 Kd;//ディフューズ
	D3DXVECTOR4 Ks;//スペキュラー
	CHAR szTextureName[512];//テクスチャーファイル名
	ID3D11ShaderResourceView* pTexture;
	DWORD dwNumFace;//そのマテリアルであるポリゴン数
	MY_SKINMATERIAL()
	{
		ZeroMemory(this,sizeof(MY_SKINMATERIAL));
	}
	~MY_SKINMATERIAL()
	{
		SAFE_RELEASE(pTexture);
	}
};

//=======================================================================================
//頂点構造体
//=======================================================================================
struct MY_SKINVERTEX
{
	D3DXVECTOR3 vPos;//頂点位置
	D3DXVECTOR3 vNorm;//頂点法線
	D3DXVECTOR2 vTex;//UV座標
	UINT bBoneIndex[4];//ボーン　番号
	float bBoneWeight[4];//ボーン　重み
	MY_SKINVERTEX()
	{
		ZeroMemory(this,sizeof(MY_SKINVERTEX));
	}
};
//=======================================================================================
//ボーン構造体
//=======================================================================================
struct BONE
{
	D3DXMATRIX mBindPose;//初期ポーズ（ずっと変わらない）
	D3DXMATRIX mNewPose;//現在のポーズ（その都度変わる）
	DWORD dwNumChild;//子の数
	int iChildIndex[50];//自分の子の”インデックス" 50個まで
	CHAR Name[256];

	BONE()
	{
		ZeroMemory(this,sizeof(BONE));
		D3DXMatrixIdentity(&mBindPose);
		D3DXMatrixIdentity(&mNewPose);
	}
};
//
//

//=======================================================================================
//派生フレーム構造体 (それぞれのメッシュ用の最終ワールド行列を追加する）
//=======================================================================================
struct MYFRAME: public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
};
//=======================================================================================
//派生メッシュコンテナー構造体(
//コンテナーがテクスチャを複数持てるようにポインターのポインターを追加する）
//=======================================================================================
struct MYMESHCONTAINER: public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight;//重みの個数（重みとは頂点への影響。）
	DWORD dwBoneNum;//ボーンの数
	LPD3DXBUFFER pBoneBuffer;//ボーン・テーブル
	D3DXMATRIX** ppBoneMatrix;//全てのボーンのワールド行列の先頭ポインター
	D3DXMATRIX* pBoneOffsetMatrices;//フレームとしてのボーンのワールド行列のポインター	
};

//=======================================================================================
//Xファイル内のアニメーション階層を読み下してくれるクラスを派生させる。
//ID3DXAllocateHierarchyは派生すること想定して設計されている。
//=======================================================================================
class MY_HIERARCHY: public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY(){}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR ,CONST D3DXMESHDATA* ,CONST D3DXMATERIAL* , 
		CONST D3DXEFFECTINSTANCE* , DWORD , CONST DWORD *, LPD3DXSKININFO , LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME );
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER );	
};

class HlAnimation_Desc : public D3DXTRACK_DESC
{
public:
	HlAnimation_Desc();
	~HlAnimation_Desc();

	
	ID3DXAnimationSet* m_pAnimSet;
	float			   m_LoopTime;
	float			   m_ShiftTime;

	
	//アニメーションを切り替え時間
	static const float m_CShiftTime;

};

class D3DXPARSER
{
private:

public:
	//=======================================================================================
	//スキンメッシュに必要な変数
	//=======================================================================================
	MY_HIERARCHY cHierarchy;
	MY_HIERARCHY* m_pHierarchy;
	LPD3DXFRAME m_pFrameRoot;
	MYMESHCONTAINER* m_pContainer;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	HRESULT LoadMeshFromX(LPDIRECT3DDEVICE9,LPSTR);
	HRESULT AllocateBoneMatrix(  LPD3DXMESHCONTAINER  );
	HRESULT AllocateAllBoneMatrices( LPD3DXFRAME  );
	MYMESHCONTAINER* FindMeshContainer(D3DXFRAME* pFrame);
	DWORD *pVerts;
	float *pWights;
	VOID UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );

	//=======================================================================================
	//ボーンを削除するためのリスト
	//=======================================================================================
	static std::vector<DWORD *>BoneList;
	static std::vector<float *>ABList;


	//=======================================================================================
	//スキンメッシュに必要な関数
	//=======================================================================================
	int GetNumVertices();					//頂点の数を取得
	int GetNumFaces();						//面の数を取得
	int GetNumMaterials();					//マテリアルの数を取得
	int GetNumUVs();						//UVの数を取得
	int GetNumBones();						//ボーンの数を取得
	int GetNumBoneVertices(int iBoneIndex);	//ボーンの頂点の数を取得
	DWORD GetBoneVerticesIndices(int iBoneIndex,int iIndexInGroup);		//ボーンのインデックスを取得
	double GetBoneVerticesWeights(int iBoneIndex,int iIndexInGroup);	//ボーンのウェイトを取得


	D3DXVECTOR3 GetVertexCoord(DWORD iIndex);
	D3DXVECTOR3 GetNormal(DWORD iIndex);
	D3DXVECTOR2 GetUV(DWORD iIndex);
	int GetIndex(DWORD iIndex);
	D3DXVECTOR4 GetAmbient(int iIndex);
	D3DXVECTOR4 GetDiffuse(int iIndex);
	D3DXVECTOR4 GetSpecular(int iIndex);
	CHAR* GetTexturePath(int index);
	float GetSpecularPower(int iIndex);
	int GeFaceMaterialIndex(int iFaceIndex);
	int GetFaceVertexIndex(int iFaceIndex,int iIndexInFace);
	D3DXMATRIX GetBindPose(int iBoneIndex);
	D3DXMATRIX GetNewPose(int iBoneIndex);
	CHAR* GetBoneName(int iBoneIndex);

	//=======================================================================================
	//アニメーションに必要な変数
	//=======================================================================================

	//アニメーション
	std::vector<HlAnimation_Desc*>m_hlAnimationList;					//アニメーションを格納するためのリスト

	//現在のアニメーショントラック
	DWORD	m_CurrentTrack = 0;											//現在のトラック

	//1つ前のアニメーショントラック
	DWORD   m_BeforeTrack = 0;											//１つまえのアニメーショントラック

	//現在のアニメーションが開始されてからの時間
	DWORD   m_AnimTime;													//現在のアニメーションが開始されたからの時間

	//アニメーションのウェイト次官を指定
	BOOL AdavancedTime(float time);										//アニメーションのウェイト時間を指定

	//アニメーションスピード
	//float m_AnimeSpeed = 0.3;
	BOOL m_AnimStopFlg = FALSE;
	void SetStop(bool _flag);

	void Delete();
};

//=======================================================================================
//class CD3DXSKINMESH
//CD3DXSKINMESH オリジナルメッシュクラス
//=======================================================================================
class CD3DXSKINMESH
{
public:
	

	//=======================================================================================
	//シェーダーに渡す値
	//=======================================================================================
	struct SHADER_SKIN_GLOBAL0
	{
		D3DXVECTOR4 vLightDir;//ライト方向
		D3DXVECTOR4 vEye;//カメラ位置
	};

	struct SHADER_SKIN_GLOBAL1
	{
		D3DXMATRIX mW;//ワールド行列
		D3DXMATRIX mWVP;//ワールドから射影までの変換行列
		D3DXVECTOR4 vAmbient;//アンビエント光
		D3DXVECTOR4 vDiffuse;//ディフューズ色
		D3DXVECTOR4 vSpecular;//鏡面反射
	};

	struct SHADER_GLOBAL_BONES
	{
		D3DXMATRIX mBone[MAX_BONES];
		SHADER_GLOBAL_BONES()
		{
			for (int i = 0; i<MAX_BONES; i++)
			{
				D3DXMatrixIdentity(&mBone[i]);
			}
		}
	};

	//=======================================================================================
	//構造体定義
	//=======================================================================================
	struct LINE_CBUFFER
	{
		D3DXMATRIX mWVP;
		D3DXVECTOR4 Color;
	};
	//=======================================================================================
	//頂点の構造体
	//=======================================================================================
	struct MY_VERTEX
	{
		D3DXVECTOR3 vPos;
		D3DXVECTOR3 vNorm;
		D3DXVECTOR2 vTex;
	};

	struct LINE_VERTEX
	{
		D3DXVECTOR3 vPos;
	};


	//=======================================================================================
	//メンバ変数
	//=======================================================================================
	HWND m_hWnd;	
	//Dx9
	LPDIRECT3D9 m_pD3d9;
	LPDIRECT3DDEVICE9 m_pDevice9;
	//Dx11
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	ID3D11SamplerState* m_pSampleLinear;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Buffer* m_pConstantBuffer0;
	ID3D11Buffer* m_pConstantBuffer1;
	ID3D11Buffer* m_pConstantBufferBone;

	//メッシュ
	D3DXMATRIX m_View;				//ビュー行列
	D3DXMATRIX m_Proj;				//プロジェクション行列
	D3DXVECTOR3 m_Eye;				//視点
	D3DXPARSER* m_pD3dxMesh;		//本体
	DWORD m_dwNumVert;				//Vertの数
	DWORD m_dwNumFace;				//面の数
	DWORD m_dwNumUV;				//UVの数
	ID3D11Buffer* m_pVertexBuffer;	//バーテックスバッファー
	ID3D11Buffer** m_ppIndexBuffer;	//インデックスバッファー
	MY_SKINMATERIAL* m_pMaterial;	//マテリアル
	DWORD m_dwNumMaterial;			//マテリアルの数

	D3DXVECTOR3 m_Pos;				//座標
	float m_Yaw;					//Y軸
	float m_Pitch;					//X軸
	float m_Roll;					//Z軸
	D3DXVECTOR3 m_Scale;			//拡大
	D3DXMATRIX m_World;				//ワールド
	D3DXMATRIX m_Rotation;			//回転
	LPD3DXMESH m_pMesh;				//メッシュ
	D3DXVECTOR3 m_Dir;				//方向
	D3DXVECTOR3 m_AxisZ;
	D3DXVECTOR3 m_AxisX;
	float m_Radius;

	
	//=======================================================================================
	//レイを可視化するための線
	//=======================================================================================
	ID3D11Buffer* m_pLineVertexBuffer;
	ID3D11Buffer* m_pLineConstantBuffer;
	ID3D11InputLayout* m_pLineVertexLayout;
	ID3D11VertexShader* m_pLineVertexShader;
	ID3D11PixelShader* m_pLinePixelShader;

	//ボーン
	int m_iNumBone;
	BONE* m_BoneArray;
	
	//=======================================================================================
	//メソッド
	//=======================================================================================
	CD3DXSKINMESH();
	~CD3DXSKINMESH();
	HRESULT InitSM(HWND _hWnd,ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext);
	HRESULT CreateIndexBuffer(DWORD dwSize,int* pIndex,ID3D11Buffer** ppIndexBuffer);
	void Render(D3DXMATRIX& , D3DXMATRIX& , D3DXVECTOR3& , D3DXVECTOR3&);
	HRESULT CreateFromX(CHAR* szFileName);
	HRESULT ReadSkinInfo(MY_SKINVERTEX*);
	//void RecursiveSetNewPoseMatrices(BONE* pBone,D3DXMATRIX* pmParent);
	void SetNewPoseMatrices(int frame);
	D3DXMATRIX GetBindPoseMatrix(int index);
	D3DXMATRIX GetCurrentPoseMatrix(int index);
	CHAR* GetBoneNames(int iBoneIndex);

	/**/
	void RenderNoAnim(D3DXMATRIX&);

	//変更したいアニメーションの番号
	VOID ChangeAnim(DWORD NewAnimNum);

	
	void RenderRay(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vRayDir, float RayLength);
};


