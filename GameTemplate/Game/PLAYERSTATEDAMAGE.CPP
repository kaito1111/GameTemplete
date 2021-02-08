#include "pch.h"
#include "Player/State/PlayerStateDamage.h"

#include "Player/Player.h"

void PlayerStateDamage::Update() {
	m_player->PlayAnimation(Player::Damage);
	if (!m_player->IsPlayAnimation()) {
		m_player->SetIdleState();
	}
}
