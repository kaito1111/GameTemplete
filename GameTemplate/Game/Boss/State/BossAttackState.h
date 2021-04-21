#pragma once
#include "IBossState.h"
class BossAttackState : public IBossState
{
private:
	BossAttackState(Boss* boss) :
		IBossState(boss) {};
	void Update()override;
};

