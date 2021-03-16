#include "pch.h"
#include "EnemyDown.h"
#include "Enemy/Enemy.h"

void EnemyDown::Update()
{
	m_enemy->PlayAnimation(Enemy::State::Down);
}
