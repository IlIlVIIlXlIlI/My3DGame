//#pragma once
//
//#include "BASE.h"
//
//class MousePointer
//{
//public:
//
//	//コンストラクタ
//	MousePointer();
//
//	//デストラクタ
//	~MousePointer();
//
//	//マウスポインタ初期化
//	void InitMousePointer(HWND);
//
//	//マウスポインタセット
//	void SetMousePointer();
//
//	//シングルトンをインスタンス化
//	static MousePointer& GetInstance()
//	{
//		static MousePointer Instance;
//		return Instance;
//	}
//
//	//ゲッター
//	inline D3DXVECTOR3 GetAng(){ return m_Ang; }
//
//private:
//
//	//マウスポインタ座標制限
//	POINT				m_BasePt;
//
//	//　マウスの速さ
//	float				m_MouseSpeed;
//
//	//　マウスの情報
//	float				m_MouseSensor;
//
//	//　センシの最大値(固定値)
//	static const float	DEFAULT_MOUSE_SPEED;
//
//	//マウスのアングル
//	D3DXVECTOR3		m_Ang;
//};
//
//#define GET_MOUSE		MousePointer::GetInstance()
//
