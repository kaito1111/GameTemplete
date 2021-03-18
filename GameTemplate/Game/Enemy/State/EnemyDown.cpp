#include "pch.h"
#include "EnemyDown.h"
#include "Enemy/Enemy.h"

void EnemyDown::Update()
{
	//死亡アニメーションを更新
	m_enemy->PlayAnimation(Enemy::State::Down);
	//アニメーションが終わったらIdleステートに変える
	if (!m_enemy->IsPlayingAnimation()) {
		DeleteGO(m_enemy);
	}
}
