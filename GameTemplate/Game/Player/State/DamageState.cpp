#include "pch.h"
#include "DamageState.h"
#include "Player/Player.h"

void DamageState::Update() {
	m_player->PlayAnimation();
	if (!m_player->IsPlayAnimation()) {
		m_player->SetIdleState();
	}
	DeleteGOs("playerAttack");
}