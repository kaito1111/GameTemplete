#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
class EnemyAttackState : public IEnemyState
{
public:
	EnemyAttackState(Enemy* en) :
		IEnemyState(en) {	}

	void Update()override;
};

