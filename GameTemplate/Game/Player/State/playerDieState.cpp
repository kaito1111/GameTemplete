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
	if (m_DieSprite->GetRezult() == 0) {
		m_fade = NewGO<Fade>(0);
		m_Rezult = m_DieSprite->GetRezult();
	}
	if (m_fade != nullptr) {
		if (m_fade->GetAlpha() >= 1.0f) {
			NewGO<ReSetGame>(0);
		}
	}
}

PlayerDieState::~PlayerDieState()
{	
	if (m_DieSprite != nullptr) {
		DeleteGO(m_DieSprite);
	}
}


