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
//	//	�Z���V�l�@�f�t�H���g4.0f
//	m_MouseSpeed = DEFAULT_MOUSE_SPEED;
//
//	//	�Z���T�[�Ɋi�[���Ă���
//	m_MouseSensor = m_MouseSpeed;
//
//	//�}�E�X�|�C���^�ꏊ�Œ�
//	m_BasePt = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
//
//	//�}�E�X�|�C���^�Z�b�g
//	ClientToScreen(_hWnd, &m_BasePt);
//	SetCursorPos(m_BasePt.x, m_BasePt.y);
//
//	//�}�E�X�|�C���^������
//	ShowCursor(FALSE);
//
//	m_Ang.x = 0.0f;
//}
//
//void MousePointer::SetMousePointer()
//{
//	const float MOUSE_ANGLE_X_UP_MAX = 40;		//	�}�E�X�̌����̌��E�l
//	const float MOUSE_ANGLE_X_DOWN_MAX = 40;
//	const float MOUSE_ANGLE_Y_MAX = 360;
//	//�}�E�X�|�C���^���W�i�[�p
//	POINT			m_Pt;
//
//	//���݂̃}�E�X�|�C���^�̈ʒu���i�[
//	GetCursorPos(&m_Pt);
//
//	//�}�E�X�̌�����ݒ�
//	m_Ang.x += (m_Pt.y - m_BasePt.y) / m_MouseSensor;
//	m_Ang.y += (m_Pt.x - m_BasePt.x) / m_MouseSensor;
//
//	//���E�l�ݒ�
//	if (m_Ang.x >  MOUSE_ANGLE_X_UP_MAX){ m_Ang.x = MOUSE_ANGLE_X_UP_MAX; }
//	if (m_Ang.x < -MOUSE_ANGLE_X_DOWN_MAX){ m_Ang.x = -MOUSE_ANGLE_X_DOWN_MAX; }
//	if (m_Ang.y >  MOUSE_ANGLE_Y_MAX){ m_Ang.y = 0; }
//	if (m_Ang.y < -MOUSE_ANGLE_Y_MAX){ m_Ang.y = 0; }
//
//	//�}�E�X�|�C���^�Z�b�g
//	SetCursorPos(m_BasePt.x, m_BasePt.y);
//}
//
