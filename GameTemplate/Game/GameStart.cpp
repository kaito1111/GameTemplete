#include "pch.h"
#include "GameStart.h"
#include "Fade.h"
#include "Game.h"

bool GameStart::Start()
{
	////////フェードを生成///////////
	m_fade = NewGO<Fade>(5, "fade");
	/////////////////////////////////
	return true;
}

void GameStart::Update()
{
	if (m_fade->GetAlpha() > 0.9) {
		////////ゲームシーンを作る//////////////////
		Game* game = NewGO<Game>(0, "game");
		game->SetLevelFilePath(L"StageLevel.tkl");
		////////////////////////////////////////////
		//タイトルを消す///
		DeleteGO("title");
		///////////////////
		//用済みなので死ぬ
		DeleteGO(this);
		///////////////////
	}
}
