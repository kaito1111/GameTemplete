#include "pch.h"
#include "EnemyDown.h"
#include "Enemy/Enemy.h"

void EnemyDown::Update()
{
	//���S�A�j���[�V�������X�V
	m_enemy->PlayAnimation(Enemy::State::Down);
	//�A�j���[�V�������I�������Idle�X�e�[�g�ɕς���
	if (!m_enemy->IsPlayingAnimation()) {
		DeleteGO(m_enemy);
	}
}
