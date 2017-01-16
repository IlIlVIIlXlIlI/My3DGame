/*----------------------------------------------------------------

スレッド管理クラス

----------------------------------------------------------------*/

#ifndef _CLASS_NAME_THREAD_H_
#define _CLASS_NAME_THREAD_H_


/*============

マクロ宣言

============*/

#define GET_THREAD CThread::GetInstance()


/*=============

Class宣言

=============*/

class CThread
{
public:

	//	初期化
	void Init();

	//	更新
	void Update();

	//	開放
	void Release();


	//	インスタンスを返す
	static CThread& GetInstance()
	{
		static CThread Instance;
		return Instance;
	}

private:


	//----------------
	//	コンストラクタ
	//----------------
	CThread();


	//--------------
	//	デストラクタ
	//--------------
	~CThread();


	//	スレッド用変数
	std::thread			m_Thread;

	//	複数スレッドで、安全に共通管理できる変数としてatomic変数を採用
	std::atomic<bool>	m_EndFlag;

};


#endif  _CLASS_NAME_THREAD_H_