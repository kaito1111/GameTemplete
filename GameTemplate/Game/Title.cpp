#include "pch.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"

bool Title::Start()
{
	m_TitleSprite = NewGO<SpriteRender>(0);
	m_TitleSprite->Init(L"Assets/sprite/title.dds");
	return true;
}

void Title::Update()
{
	if (g_pad[0].IsPress(enButtonA)) {
		m_fade = NewGO<Fade>(0,"fade");
		if (m_fade->GetAlpha() > 1.0f) {
			Game* game = NewGO<Game>(0, "game");
			game->SetLevelFilePath(L"StageLevel.tkl");
			DeleteGO(this);
		}
	}
}
