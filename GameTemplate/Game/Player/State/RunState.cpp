#include "pch.h"
#include "RunState.h"
#include "Player/Player.h"

void RunState::Update() {
	m_player->SetMulAnimSpeed(1.0f);
	m_player->PlayAnimation();
	
	m_player->TryChangeIdleState();
	m_player->TryChangeBackStepState();
	m_player->TryChangeAttackState();
	m_player->TryChangeRollingAttackState();
}