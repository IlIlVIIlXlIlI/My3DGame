#pragma once
#include "BASE.h"


class BLACKBAR
{
private:
	
	
public:
	BLACKBAR();					//コンストラクタ

	float	posCount = 0.0;		//ポジションカウント
	bool	onFlg = FALSE;		//黒帯出現中かどうか
	
	/*黒帯を出現させる計算*/
	void Sum();

	
	
};