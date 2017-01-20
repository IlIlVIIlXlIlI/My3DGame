#include "BlackBar.h"

BLACKBAR::BLACKBAR()
{
	posCount = 0.0;

	onFlg = FALSE;
}

void BLACKBAR::Sum()
{
	if (posCount >= 89)posCount = 89;
	posCount++;
}