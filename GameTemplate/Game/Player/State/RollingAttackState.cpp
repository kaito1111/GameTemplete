#include "pch.h"
#include "RollingAttackState.h"
#include "Player/Player.h"

void RollingAttackState::Update()
{
	m_player->SetMulAnimSpeed(1.0f);

	m_player->PlayAnimation();

	m_player->IsStaminaRest();
	if (m_player->IsPlayAnimation() == false) {
		m_player->SetIdleState();
	}
}