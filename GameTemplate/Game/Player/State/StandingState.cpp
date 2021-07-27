#include "pch.h"
#include "StandingState.h"
#include "Player/Player.h"
#include "GameStart.h"

void StandingState::Update()
{
	m_player->PlayAnimation();
	if (!m_player->IsPlayAnimation()) {
		if (m_GameStart == nullptr) {
			m_GameStart = NewGO<GameStart>(0, "GameStart");
		}
	}
}
