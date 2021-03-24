#include "pch.h"
#include "PlayerStateDamage.h"
#include "Player/Player.h"

void PlayerStateDamage::Update() {
	m_player->PlayAnimation();
	if (!m_player->IsPlayAnimation()) {
		m_player->SetIdleState();
	}
	DeleteGOs("playerAttack");
}