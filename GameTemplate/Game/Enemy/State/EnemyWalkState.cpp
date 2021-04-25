#include "pch.h"
#include "EnemyWalkState.h"
#include"Enemy/Enemy.h"

void EnemyWalkState::Update() {
	m_enemy->PlayAnimation(Enemy::State::Walk);
	m_enemy->EnemyWalk();
	if (m_enemy->GetMoveSpeed().Length() >500.0f) {
		m_enemy->SetIdleState();
		return;
	}
	m_enemy->TryChangeAttackState();
}