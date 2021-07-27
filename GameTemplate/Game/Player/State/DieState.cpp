#include "pch.h"
#include "DieState.h"
#include "Player/Player.h"
#include "Player/DieSprite.h"
#include "Fade.h"
#include "ReSetGame.h"

void DieState::Update()
{
	m_player->PlayAnimation();
}

void DieState::Delete()
{
	if (m_DieSprite != nullptr) {
		DeleteGO(m_DieSprite);
	}
}

void DieState::ReStart()
{
}

DieState::~DieState()
{
}


