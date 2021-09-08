#include "pch.h"
#include "HuntedSprite.h"
#include "ReSetGame.h"
#include "Fade.h"
#include "Title/Title.h"
#include "ReSetTitle.h"

namespace {
	const float addSpriteAlpha = 0.05f;
	const float priority = 4;
	const float RestarPos = -100.0f;
	const float TitlePos = -350.0f;
}
bool HuntedSprite::Start()
{
	m_HuntSprite = NewGO<SpriteRender>(priority+1);
	m_HuntSprite->Init(L"PlayerHunted.dds", 1024, 1024);
	m_HuntSprite->SetAlpha(m_HuntAlpha);
	m_BrackSprite = NewGO<SpriteRender>(priority);
	m_BrackSprite->Init(L"Brack.dds");
	m_BrackSprite->SetAlpha(m_HuntAlpha);
	m_HuntSound.Init(L"Hunted.wav"); 
	m_HuntSound.SetVolume(20.0f);
	m_HuntSound.Play();
	return true;
}

void HuntedSprite::Update()
{
	m_HuntAlpha += addSpriteAlpha;
	if (m_HuntAlpha > 0.5f) {
		m_BrackSprite->SetAlpha(0.5f);
	}
	else {
		m_BrackSprite->SetAlpha(m_HuntAlpha);
	}
	if (m_HuntAlpha > 1.0f) {
		m_HuntAlpha = 1.0f;
	}
	//タイトルが選ばれると
	if (m_HuntAlpha >= 1.0f&&
		g_pad[0].IsPressAnyKey() &&
		m_ReSet == false) {
		ReSetTitle* m_Title = NewGO<ReSetTitle>(0, "resettitle");
		m_ReSet = true;
	}
	m_HuntSprite->SetAlpha(m_HuntAlpha);
}

void HuntedSprite::OnDestroy()
{
	DeleteGO(m_HuntSprite);
	DeleteGO(m_BrackSprite);
}
