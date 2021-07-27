#include "pch.h"
#include "BackStepState.h"
#include "Player/Player.h"

void BackStepState::Update() {
	m_player->SetMulAnimSpeed(1.0f);

	m_player->PlayAnimation();


	if (m_player->IsPlayAnimation() == false) {
		m_player->SetIdleState();
	}
}