#pragma once
#include "IBossState.h"
class BossWalkState : public IBossState
{
public:
	BossWalkState(Boss* boss) :
		IBossState(boss) {};
	void Update()override;
};

