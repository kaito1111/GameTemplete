#include "pch.h"
#include "PlayerStateRollingAttack.h"
#include "Player/Player.h"

void PlayerStateRollingAttack::Update()
{
	m_player->SetMulAnimSpeed(1.0f);

	m_player->PlayAnimation();

	if (m_player->IsPlayAnimation() == false) {
		m_player->SetIdleState();
	}
}
