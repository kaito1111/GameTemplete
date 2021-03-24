#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
class EnemyDamageState : public IEnemyState
{
public:
	EnemyDamageState(Enemy* en) :
		IEnemyState(en) {};
	~EnemyDamageState() {};

	void Update()override;
};

