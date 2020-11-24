#include "pch.h"
#include "PlayerStateBackStep.h"
#include "Player/Player.h"

void PlayerStateBackStep::Update() {
	m_player->SetMulAnimSpeed(1.0f);

	m_player->PlayAnimation(Player::AnimePattern::Back);


	if (m_player->IsPlayAnimation() == false) {
		m_player->ChangeState(Player::State_Idle);
	}
}