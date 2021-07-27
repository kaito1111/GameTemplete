#include "pch.h"
#include "TitleState.h"
#include "Player/Player.h"

void TitleState::Update()
{
	m_player->PlayAnimation();
}
