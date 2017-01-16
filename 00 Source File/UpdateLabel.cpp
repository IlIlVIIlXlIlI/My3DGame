#include "UpdateLabel.h"

void LABELCAL::UpdateLabel()
{
	/*「UPDATE」の表示の仕方を計算*/
	if (GetAsyncKeyState('Y') && 0x8000) updateFlg = TRUE;
	if (updateFlg == TRUE)
	{
		if (markState == 0) { markCount -= 2.5f; }
		if (markCount <= 350) { markState = 1; }
		if (markState == 1) { markCount -= 2.0; }
		if (markState == 1 && markCount <= 300) { markCount = 300; markState = 2; }

		if (markState == 2)
		{
			secondCount++;
		}
		if (secondCount >= 300)
		{
			markState = 3;
			secondCount = 300;
		}

		if (markState == 3)
		{
			markCount += 2.5;
		}

		if (markState == 3 && markCount >= WINDOW_WIDTH - 400)
		{
			markState = 0;
			markCount = WINDOW_WIDTH - 400;
			secondCount = 0.0;
			updateFlg = FALSE;
		}
	}
}

void LABELCAL::MissionLabel()
{
	if (labelflg == FALSE) { labelCount -= 2.5f; }
	if (labelCount <= 350) { labelflg = TRUE; }
	if (labelflg == TRUE) { labelCount -= 2.0; }
	if (labelCount <= 300) { labelCount = 300; }
}