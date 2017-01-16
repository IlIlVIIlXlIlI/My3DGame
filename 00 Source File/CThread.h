/*----------------------------------------------------------------

�X���b�h�Ǘ��N���X

----------------------------------------------------------------*/

#ifndef _CLASS_NAME_THREAD_H_
#define _CLASS_NAME_THREAD_H_


/*============

�}�N���錾

============*/

#define GET_THREAD CThread::GetInstance()


/*=============

Class�錾

=============*/

class CThread
{
public:

	//	������
	void Init();

	//	�X�V
	void Update();

	//	�J��
	void Release();


	//	�C���X�^���X��Ԃ�
	static CThread& GetInstance()
	{
		static CThread Instance;
		return Instance;
	}

private:


	//----------------
	//	�R���X�g���N�^
	//----------------
	CThread();


	//--------------
	//	�f�X�g���N�^
	//--------------
	~CThread();


	//	�X���b�h�p�ϐ�
	std::thread			m_Thread;

	//	�����X���b�h�ŁA���S�ɋ��ʊǗ��ł���ϐ��Ƃ���atomic�ϐ����̗p
	std::atomic<bool>	m_EndFlag;

};


#endif  _CLASS_NAME_THREAD_H_