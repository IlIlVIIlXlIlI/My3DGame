//#include "CSystem.h"
//
//
//
//MousePointer::MousePointer()
//{
//
//}
//
//MousePointer::~MousePointer()
//{
//
//}
//
//void MousePointer::InitMousePointer(HWND _hWnd)
//{
//	//	センシ値　デフォルト4.0f
//	m_MouseSpeed = DEFAULT_MOUSE_SPEED;
//
//	//	センサーに格納しておく
//	m_MouseSensor = m_MouseSpeed;
//
//	//マウスポインタ場所固定
//	m_BasePt = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
//
//	//マウスポインタセット
//	ClientToScreen(_hWnd, &m_BasePt);
//	SetCursorPos(m_BasePt.x, m_BasePt.y);
//
//	//マウスポインタを消す
//	ShowCursor(FALSE);
//
//	m_Ang.x = 0.0f;
//}
//
//void MousePointer::SetMousePointer()
//{
//	const float MOUSE_ANGLE_X_UP_MAX = 40;		//	マウスの向きの限界値
//	const float MOUSE_ANGLE_X_DOWN_MAX = 40;
//	const float MOUSE_ANGLE_Y_MAX = 360;
//	//マウスポインタ座標格納用
//	POINT			m_Pt;
//
//	//現在のマウスポインタの位置を格納
//	GetCursorPos(&m_Pt);
//
//	//マウスの向きを設定
//	m_Ang.x += (m_Pt.y - m_BasePt.y) / m_MouseSensor;
//	m_Ang.y += (m_Pt.x - m_BasePt.x) / m_MouseSensor;
//
//	//限界値設定
//	if (m_Ang.x >  MOUSE_ANGLE_X_UP_MAX){ m_Ang.x = MOUSE_ANGLE_X_UP_MAX; }
//	if (m_Ang.x < -MOUSE_ANGLE_X_DOWN_MAX){ m_Ang.x = -MOUSE_ANGLE_X_DOWN_MAX; }
//	if (m_Ang.y >  MOUSE_ANGLE_Y_MAX){ m_Ang.y = 0; }
//	if (m_Ang.y < -MOUSE_ANGLE_Y_MAX){ m_Ang.y = 0; }
//
//	//マウスポインタセット
//	SetCursorPos(m_BasePt.x, m_BasePt.y);
//}
//
