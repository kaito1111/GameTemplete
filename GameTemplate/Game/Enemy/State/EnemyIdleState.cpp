#include "EnemyIdleState.h"

#include"Enemy/Enemy.h"

void EnemyIdleState::Update()
{
	//待機アニメーションを更新
	m_enemy->PlayAnimation(Enemy::State::Idle);
	//歩くのか判定
	m_enemy->TryChangeWalk();
	//攻撃するか判定
	m_enemy->TryChangeAttackState();
}
