#include "pch.h"
#include "PlayerStateRun.h"
#include "Player/Player.h"

void PlayerStateRun::Update() {
	m_player->SetMulAnimSpeed(1.0f);
	m_player->PlayAnimation(Player::walk);
	
	m_player->TryChangeIdleState();
	m_player->TryChangeBackStepState();
	m_player->TryChangeAttackState();
	m_player->TryChangeRollingAttackState();
}