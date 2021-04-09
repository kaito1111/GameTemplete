#pragma once
#include "Boss/Boss.h"
class IBossState
{
	IBossState(Boss* boss)
		: m_Boss(boss) 
	{};
	~IBossState() {};

	virtual void Start() {};
	virtual void Update() = 0;


private:
	Boss* m_Boss = nullptr;
};

