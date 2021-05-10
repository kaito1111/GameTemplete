#include "pch.h"
#include "ReSetGame.h"
#include "Game.h"

bool ReSetGame::Start()
{
	DeleteGO("game");
	Game* m_game = NewGO<Game>(0, "game");
	m_game->SetLevelFilePath(L"StageLevel.tkl");
	DeleteGO(this);
	return true;
}
