//#pragma once
//
//#include "BASE.h"
//
//class MousePointer
//{
//public:
//
//	//�R���X�g���N�^
//	MousePointer();
//
//	//�f�X�g���N�^
//	~MousePointer();
//
//	//�}�E�X�|�C���^������
//	void InitMousePointer(HWND);
//
//	//�}�E�X�|�C���^�Z�b�g
//	void SetMousePointer();
//
//	//�V���O���g�����C���X�^���X��
//	static MousePointer& GetInstance()
//	{
//		static MousePointer Instance;
//		return Instance;
//	}
//
//	//�Q�b�^�[
//	inline D3DXVECTOR3 GetAng(){ return m_Ang; }
//
//private:
//
//	//�}�E�X�|�C���^���W����
//	POINT				m_BasePt;
//
//	//�@�}�E�X�̑���
//	float				m_MouseSpeed;
//
//	//�@�}�E�X�̏��
//	float				m_MouseSensor;
//
//	//�@�Z���V�̍ő�l(�Œ�l)
//	static const float	DEFAULT_MOUSE_SPEED;
//
//	//�}�E�X�̃A���O��
//	D3DXVECTOR3		m_Ang;
//};
//
//#define GET_MOUSE		MousePointer::GetInstance()
//
