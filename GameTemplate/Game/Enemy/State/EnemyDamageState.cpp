#include "pch.h"
#include "EnemyDamageState.h"
#include "Enemy/Enemy.h"

void EnemyDamageState::Update()
{
	//ダメージアニメーションを更新
	m_enemy->PlayAnimation(Enemy::State::Damege);
	//アニメーションが終わったらIdleステートに変える
	if (m_enemy->IsPlayingAnimation() == false) {
		m_enemy->SetIdleState();
	}
}
