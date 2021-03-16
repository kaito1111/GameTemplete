#include "pch.h"
#include "Title.h"

bool Title::Start()
{
	m_TitleSprite = NewGO<SpriteRender>(0);
	m_TitleSprite->Init(L"Assets/sprite/title.dds");
	return true;
}

void Title::Update()
{
	
}
