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
	//	スレッドのコンストラクタに、直接関数を作っておく
	//--------------------------------------------------


	/*LoadThread(Lambda関数)-------------------------->

		読み込みスレッド開始
		※別スレッドで稼動
		※読み込み関数のみ行う


		[&]		:	全参照キャプチャ
		()		:	引数なし

		return	:	戻り値なし

	<------------------------------------------------*/
	std::thread LoadThread(
		[&]
		()
		{

			//================
			//	データ読み込み
			//================
			/*ロードしたいファイル*/
			//while (1);



			//	エンドフラグをtrueに
			m_EndFlag = true;
		}
	);


	/*DrawThread(Lambda関数)------------------------->
	
		描画スレッド開始
		※別スレッドで稼動
		※描画のみを行う


		[&]		:	全参照キャプチャ
		()		:	引数なし

		return	:	戻り値なし

	<-----------------------------------------------*/
	std::thread DrawThread(
		[&]
		()
		{
			int cnt = 0;

			while (1)
			{
				//	アルファ値
				float alpha = sinf(D3DXToRadian(cnt * 10));
				alpha = alpha * 0.5f + 0.5f;

				// ----------------------------------- //

#ifdef _DEBUG
				//MessageBoxA(nullptr, "マルチスレッド実行中",nullptr, MB_OK);
				//cout << "マルチスレッド実行中　経過時間：" << cnt << std::endl;
				
				//d3d.DrawFont("マルチスレッド", D3DCOLOR_ARGB(255, 255, 0, 255), &mT);
#endif // _DEBUG
				// ----------------------------------- //
				

				Sleep(32);
				//	ロードスレッドが終了しているなら終わる
				if (m_EndFlag)
				{
					break;
				}

				cnt++;
			}

		}
	);


	//	読み込みスレッドの終了まで待機する
	LoadThread.join();

	//	描画スレッドまで待機する
	DrawThread.join();
}


void CThread::Release()
{
}