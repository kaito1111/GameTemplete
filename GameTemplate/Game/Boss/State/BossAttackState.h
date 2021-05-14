#pragma once
#include "IBossState.h"
class BossAttackState : public IBossState
{
public:
	BossAttackState(Boss* boss) :
		IBossState(boss) {};
	~BossAttackState()
	{

	}
	void Update()override;
};

