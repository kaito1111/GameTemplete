#pragma once
#include "IBossState.h"
class BossNormalRoar:public IBossState
{
public:
	BossNormalRoar(Boss* boss) :
		IBossState(boss) {};

	void Update()override;
};

