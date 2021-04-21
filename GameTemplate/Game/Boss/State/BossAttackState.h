#pragma once
#include "IBossState.h"
class BossAttackState : public IBossState
{
public:
	BossAttackState(Boss* boss) :
		IBossState(boss) {};
	void Update()override;
};

