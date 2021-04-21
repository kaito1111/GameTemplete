#pragma once
#include "IBossState.h"
class BossAppearanceRoarState : public IBossState
{
public:
	BossAppearanceRoarState(Boss* boss) :
		IBossState(boss) {};
	
	void Update()override;


 };

