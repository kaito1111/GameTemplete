#include "pch.h"
#include "PlayerStateBackStep.h"
#include "Player/Player.h"

void PlayerStateBackStep::Update() {
	m_player->SetMulAnimSpeed(1.0f);

	m_player->PlayAnimation(Player::Back);


	if (m_player->IsPlayAnimation() == false) {
		m_player->SetIdleState();
	}
}