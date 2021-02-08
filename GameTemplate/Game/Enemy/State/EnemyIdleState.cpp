#include "EnemyIdleState.h"

#include"Enemy/Enemy.h"

void EnemyIdleState::Update()
{
	m_enemy->PlayAnimation(Enemy::State::Idle);

	m_enemy->TryChangeWalk();

	m_enemy->TryChangeAttackState();
}
