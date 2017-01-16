#include <windows.h>
#include "DIRECTOR.h"

INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,INT)
{
//#ifdef _DEBUG
	FILE *fp;
	::AllocConsole();
	freopen_s(&fp, "CON", "w", stdout);
//#endif

	// ���������[�N��m�点��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DIRECTOR* pDirector=new DIRECTOR;
	if(pDirector==nullptr)
	{
		assert((pDirector == nullptr), "XXX:�s���Ȓl�ł�");
		MessageBox(0,"�N���X�������s�@�A�v�����I�����܂�",nullptr,MB_OK);
		return 0;
	}
	//�i�s�̓f�B���N�^�[��
	pDirector->Run(hInstance);

	//�A�v���I��
	delete pDirector;

//#ifdef _DEBUG
	fclose(fp);
//#endif

	return 0;
}