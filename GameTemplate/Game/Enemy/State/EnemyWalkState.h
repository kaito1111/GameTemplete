#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
class EnemyWalkState : public IEnemyState
{
public:
	EnemyWalkState(Enemy* en) :
		IEnemyState(en) {};
	~EnemyWalkState() {};
	
private:
	void Update() override;
};
