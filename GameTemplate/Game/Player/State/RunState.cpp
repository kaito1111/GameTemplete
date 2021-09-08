#include "pch.h"
#include "RunState.h"
#include "Player/Player.h"

void RunState::Update() {
		m_player->PlayAnimation();
	float mulSpeed = 0.0f;
	if (g_pad[0].IsPress(enButtonA)) {
		if (m_player->GetStamina() > Player::StaminaCostList::StaminaRun) {
			float SubStamina = m_player->GetStamina() - Player::StaminaCostList::StaminaRun;
			m_player->SetStamina(SubStamina);
		m_player->IsStaminaRest();
		mulSpeed = 1.0f;
		}
		else {
			//スタミナ切れ
			m_player->SetStamina(0.0f);
		}
	}
	m_player->SetMulAnimSpeed(1.0f + mulSpeed);

	m_player->TryChangeIdleState();
	m_player->TryChangeBackStepState();
	m_player->TryChangeAttackState();
	m_player->TryChangeRollingAttackState();
}