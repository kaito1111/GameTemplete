#include "pch.h"
#include "RollingState.h"
#include "Player/Player.h"

void RollingState::Update() {
	m_player->SetMulAnimSpeed(1.0f);

	m_player->PlayAnimation();

	m_player->IsStaminaRest();

	if (m_player->IsPlayAnimation() == false) {
		m_player->SetIdleState();
	}
}