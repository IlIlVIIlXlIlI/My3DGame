#pragma comment
#include "BASE.h"

class LABELCAL
{
private:

public:
	float markCount = WINDOW_WIDTH - 400;	//Update�̏������W
	char markState = 0;						//���
	float secondCount = 0.0f;				//Update���߂�n�߂�܂ł̎���

	bool updateFlg = FALSE;					//Update�����s����Ă��邩


	float labelCount = 550;					//���x���̏o�n�߂鎞��
	float labelflg = FALSE;					//���

	/*�uUPDATE�v�̕�����\��������v�Z*/
	void UpdateLabel();

	/*�uMission�v��\��������v�Z*/
	void MissionLabel();
};
