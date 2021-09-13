#include "pch.h"
#include "GameStart.h"
#include "Fade.h"
#include "Game.h"

bool GameStart::Start()
{
	////////�t�F�[�h�𐶐�///////////
	m_fade = NewGO<Fade>(5, "fade");
	/////////////////////////////////
	return true;
}

void GameStart::Update()
{
	if (m_fade->GetAlpha() > 0.9) {
		////////�Q�[���V�[�������//////////////////
		Game* game = NewGO<Game>(0, "game");
		game->SetLevelFilePath(L"StageLevel.tkl");
		////////////////////////////////////////////
		//�^�C�g��������///
		DeleteGO("title");
		///////////////////
		//�p�ς݂Ȃ̂Ŏ���
		DeleteGO(this);
		///////////////////
	}
}
