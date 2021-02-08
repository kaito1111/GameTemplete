#include "pch.h"
#include "PlayerStateDamage.h"
#include "Player/Palayer.h"

void PlayerStateDamage::Update() {
	m_player->PlayAnimation(Player::Damage);
	if (!m_palyer->IsPlayAnimation()) {
		m_player->ChangeState(Player::State_Damage);
	}
}