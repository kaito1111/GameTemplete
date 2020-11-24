#include "pch.h"
#include "PlayerStateAttack.h"
#include "Player/Player.h"

void PlayerStateAttack::Update()
{
	m_player->SetMulAnimSpeed(1.0f);

	m_player->PlayAnimation(Player::AnimePattern::Attack);

	if(m_player->IsPlayAnimation()==false){
		m_player->ChangeState(Player::State::State_Idle);
	}
}
