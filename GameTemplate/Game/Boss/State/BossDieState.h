#pragma once
#include "IBossState.h"
class BossDieState : public IBossState 
{
public:
	BossDieState(Boss* boss) :
		IBossState(boss) {};

	void Update()override;
	
};

