#include "pch.h"
#include "EnemyDamageState.h"
#include "Enemy/Enemy.h"

void EnemyDamageState::Update()
{
	m_enemy->PlayAnimation(Enemy::State::Damege);
	if (m_enemy->IsPlayingAnimation() == false) {
		m_enemy->SetIdleState();
	}
}
