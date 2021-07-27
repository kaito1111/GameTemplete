#include "pch.h"
#include "ReSetTitle.h"
#include "Title/Title.h"
#include "Fade.h"
#include "Game.h"

bool ReSetTitle::Start()
{
	m_fade = NewGO<Fade>(0);
	return true;
}

void ReSetTitle::Update()
{
	if (m_fade->GetAlpha() > 0.9f) {
		Game* m_game = FindGO<Game>("game");
		DeleteGO(m_game);
		m_game = nullptr;
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}