#include "pch.h"
#include "ReSetGame.h"
#include "Game.h"
#include "Fade.h"

bool ReSetGame::Start()
{
	m_Fade = NewGO<Fade>(0);
	return true;
}

void ReSetGame::Update()
{
	if (m_Fade->GetAlpha() > 0.9f) {
		Game* m_game = FindGO<Game>("game");
		DeleteGO(m_game);
		m_game = NewGO<Game>(0, "game");
		m_game->SetLevelFilePath(L"StageLevel.tkl");
		DeleteGO(this);
	}
}
