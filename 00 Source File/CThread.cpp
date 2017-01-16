#include "BASE.h"
#include <iostream>

using namespace std;

CThread::CThread()
	:
	m_EndFlag(false)
{

}


CThread::~CThread()
{
	m_EndFlag = false;
}


void CThread::Init()
{
	//m_Thread;
}


void CThread::Update()
{
	//--------------------------------------------------
	//	�X���b�h�̃R���X�g���N�^�ɁA���ڊ֐�������Ă���
	//--------------------------------------------------


	/*LoadThread(Lambda�֐�)-------------------------->

		�ǂݍ��݃X���b�h�J�n
		���ʃX���b�h�ŉғ�
		���ǂݍ��݊֐��̂ݍs��


		[&]		:	�S�Q�ƃL���v�`��
		()		:	�����Ȃ�

		return	:	�߂�l�Ȃ�

	<------------------------------------------------*/
	std::thread LoadThread(
		[&]
		()
		{

			//================
			//	�f�[�^�ǂݍ���
			//================
			/*���[�h�������t�@�C��*/
			//while (1);



			//	�G���h�t���O��true��
			m_EndFlag = true;
		}
	);


	/*DrawThread(Lambda�֐�)------------------------->
	
		�`��X���b�h�J�n
		���ʃX���b�h�ŉғ�
		���`��݂̂��s��


		[&]		:	�S�Q�ƃL���v�`��
		()		:	�����Ȃ�

		return	:	�߂�l�Ȃ�

	<-----------------------------------------------*/
	std::thread DrawThread(
		[&]
		()
		{
			int cnt = 0;

			while (1)
			{
				//	�A���t�@�l
				float alpha = sinf(D3DXToRadian(cnt * 10));
				alpha = alpha * 0.5f + 0.5f;

				// ----------------------------------- //

#ifdef _DEBUG
				//MessageBoxA(nullptr, "�}���`�X���b�h���s��",nullptr, MB_OK);
				//cout << "�}���`�X���b�h���s���@�o�ߎ��ԁF" << cnt << std::endl;
				
				//d3d.DrawFont("�}���`�X���b�h", D3DCOLOR_ARGB(255, 255, 0, 255), &mT);
#endif // _DEBUG
				// ----------------------------------- //
				

				Sleep(32);
				//	���[�h�X���b�h���I�����Ă���Ȃ�I���
				if (m_EndFlag)
				{
					break;
				}

				cnt++;
			}

		}
	);


	//	�ǂݍ��݃X���b�h�̏I���܂őҋ@����
	LoadThread.join();

	//	�`��X���b�h�܂őҋ@����
	DrawThread.join();
}


void CThread::Release()
{
}