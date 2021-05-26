#include "pch.h"
#include "playerDieState.h"
#include "Player/Player.h"
#include "Player/DieSprite.h"
#include "Fade.h"
#include "ReSetGame.h"

void PlayerDieState::Update()
{
	m_player->PlayAnimation();
	if (!m_player->IsPlayAnimation()) {
		ReStart();
	}
}

void PlayerDieState::ReStart()
{
	if (
		m_DieSprite->GetRezult() == 0&&
		m_resetGame==nullptr
		) {
		m_resetGame = NewGO<ReSetGame>(0);
	}
}

PlayerDieState::~PlayerDieState()
{
	if (m_DieSprite != nullptr) {
		DeleteGO(m_DieSprite);
	}
}


