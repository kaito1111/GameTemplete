#pragma once
#include "IEnemyState.h"
class Enemy;
class EnemyIdleState : public IEnemyState
{
public:
	EnemyIdleState(Enemy* en):
		IEnemyState(en) 
	{
	};
	~EnemyIdleState() {};

private:
	void Update()override;
};
