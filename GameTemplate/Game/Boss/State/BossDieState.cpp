#include "pch.h"
#include "BossDieState.h"
#include "Player/Player.h"

void BossDieState::Update()
{
	m_Boss->PlayAnimation();
	if (!m_Boss->IsPlayAnimation()) {
		Player* player = FindGO<Player>("player");
		player->SetClearState();
	}
}
