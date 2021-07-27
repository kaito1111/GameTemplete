#include "pch.h"
#include "GameStart.h"
#include "Fade.h"
#include "Game.h"

bool GameStart::Start()
{
	m_fade = NewGO<Fade>(0, "fade");
	return true;
}

void GameStart::Update()
{
	if (m_fade->GetAlpha() > 0.9) {
		Game* game = NewGO<Game>(0, "game");
		game->SetLevelFilePath(L"StageLevel.tkl");
		DeleteGO("title");
		DeleteGO(this);
	}
}
