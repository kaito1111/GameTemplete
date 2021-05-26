#include "pch.h"
#include "ReSetGame.h"
#include "Game.h"
#include "Fade.h"

bool ReSetGame::Start()
{
	return true;
}

void ReSetGame::Update()
{
	if (m_Fade->GetAlpha() > 1.0f) {
		DeleteGO("game");
		Game* m_game = NewGO<Game>(0, "game");
		m_game->SetLevelFilePath(L"StageLevel.tkl");
		DeleteGO(this);
	}
}
