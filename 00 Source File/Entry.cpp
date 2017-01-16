#include <windows.h>
#include "DIRECTOR.h"

INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,INT)
{
//#ifdef _DEBUG
	FILE *fp;
	::AllocConsole();
	freopen_s(&fp, "CON", "w", stdout);
//#endif

	// メモリリークを知らせる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DIRECTOR* pDirector=new DIRECTOR;
	if(pDirector==nullptr)
	{
		assert((pDirector == nullptr), "XXX:不正な値です");
		MessageBox(0,"クラス生成失敗　アプリを終了します",nullptr,MB_OK);
		return 0;
	}
	//進行はディレクターに
	pDirector->Run(hInstance);

	//アプリ終了
	delete pDirector;

//#ifdef _DEBUG
	fclose(fp);
//#endif

	return 0;
}