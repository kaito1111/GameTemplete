#include "pch.h"
#include "EnemyDamageState.h"
#include "Enemy/Enemy.h"

void EnemyDamageState::Update()
{
	//�_���[�W�A�j���[�V�������X�V
	m_enemy->PlayAnimation(Enemy::State::Damege);
	//�A�j���[�V�������I�������Idle�X�e�[�g�ɕς���
	if (m_enemy->IsPlayingAnimation() == false) {
		m_enemy->SetIdleState();
	}
}
