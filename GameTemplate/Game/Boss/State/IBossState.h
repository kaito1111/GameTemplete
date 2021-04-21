#pragma once
#include "Boss/Boss.h"
class IBossState
{
public:
	IBossState(Boss* boss)
		: m_Boss(boss) 
	{};
	~IBossState() {};

	virtual void Start() {};
	virtual void Update() = 0;


protected:
	Boss* m_Boss = nullptr;
};

