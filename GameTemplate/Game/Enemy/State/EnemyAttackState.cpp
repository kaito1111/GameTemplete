#include "pch.h"
#include "EnemyAttackState.h"
#include "Enemy/Enemy.h"

void EnemyAttackState::Update()
{
	m_enemy->PlayAnimation(Enemy::State::Attack);
	if (m_enemy->IsPlayingAnimation() == false) {
		m_enemy->SetIdleState();
	}
}
