#pragma once

#include "BASE.h"
#include "CharacterBase.h"


class Enemy : public ChrBase
{
private:
	

public:
	Enemy();
	virtual ~Enemy();

	enum Enemy_Status
	{
		STANDING_STATUS, //0:í èÌ(óßÇø)

		ATTACK_STATUS,	 //1:çUåÇ
	};

	Enemy_Status m_EnemyStatus = STANDING_STATUS;

};
