#include "pch.h"
#include "EnemyDown.h"
#include "Enemy/Enemy.h"

void EnemyDown::Update()
{
	//���S�A�j���[�V�������X�V
	m_enemy->PlayAnimation(Enemy::State::Down);
}
