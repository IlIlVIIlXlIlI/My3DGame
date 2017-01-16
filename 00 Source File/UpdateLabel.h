#pragma comment
#include "BASE.h"

class LABELCAL
{
private:

public:
	float markCount = WINDOW_WIDTH - 400;	//Updateの初期座標
	char markState = 0;						//状態
	float secondCount = 0.0f;				//Updateが戻り始めるまでの時間

	bool updateFlg = FALSE;					//Updateが実行されているか


	float labelCount = 550;					//ラベルの出始める時間
	float labelflg = FALSE;					//状態

	/*「UPDATE」の文字を表示させる計算*/
	void UpdateLabel();

	/*「Mission」を表示させる計算*/
	void MissionLabel();
};
