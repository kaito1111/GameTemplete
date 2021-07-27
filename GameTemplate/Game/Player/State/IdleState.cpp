#include "pch.h"
#include "Player/Player.h"
#include "IdleState.h"

void IdleState::Update()
{
	m_player->SetMulAnimSpeed(1.0f);
	
	m_player->PlayAnimation();

	m_player->TryChangeMoveState();
	
	m_player->TryChangeBackStepState();

	m_player->TryChangeAttackState();
	
	m_player->TryChangeRollingAttackState();

}