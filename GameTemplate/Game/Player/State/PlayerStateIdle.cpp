#include "pch.h"
#include "Player/Player.h"
#include "PlayerStateIdle.h"

void PlayerStateIdle::Update()
{
	m_player->SetMulAnimSpeed(1.0f);
	
	m_player->PlayAnimation(Player::idle);

	m_player->TryChangeMoveState();
	
	m_player->TryChangeBackStepState();

	m_player->TryChangeAttackState();
	
	m_player->TryChangeRollingAttackState();

}