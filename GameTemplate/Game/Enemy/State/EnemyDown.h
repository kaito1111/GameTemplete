#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
class EnemyDown : public IEnemyState
{
public:
	EnemyDown(Enemy* en) :
		IEnemyState(en) {};
	~EnemyDown() {};

	void Update();
	bool IsPossibleHpDown() {
		return false;
	}
};

