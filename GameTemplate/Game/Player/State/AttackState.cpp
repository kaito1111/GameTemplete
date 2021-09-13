#include "pch.h"
#include "AttackState.h"
#include "Player/Player.h"

void AttackState::Update()
{
	m_player->SetMulAnimSpeed(2.0f);

	m_player->PlayAnimation();
	m_player->IsStaminaRest();
	if(m_player->IsPlayAnimation()==false){
		m_player->SetIdleState();
	}
}