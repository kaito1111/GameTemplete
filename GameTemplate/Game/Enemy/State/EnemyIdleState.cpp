#include "EnemyIdleState.h"

#include"Enemy/Enemy.h"

void EnemyIdleState::Update()
{
	//�ҋ@�A�j���[�V�������X�V
	m_enemy->PlayAnimation(Enemy::State::Idle);
	//�����̂�����
	m_enemy->TryChangeWalk();
	//�U�����邩����
	m_enemy->TryChangeAttackState();
}
