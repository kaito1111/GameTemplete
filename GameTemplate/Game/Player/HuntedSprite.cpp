#include "pch.h"
#include "HuntedSprite.h"

namespace {
	float addSpriteAlpha = 0.01f;
	float priority = 0;
}
bool HuntedSprite::Start()
{
	m_HuntSprite = NewGO<SpriteRender>(priority);
	m_HuntSprite->Init(L"PlayerHunted.dds");
	m_HuntSprite->SetAlpha(m_HuntAlpha);
	//ロゴはDieスプライトより手前に来てほしいので＋１する
	m_LogoSprite = NewGO<SpriteRender>(priority + 1);
	m_LogoSprite->Init(L"PlayerHuntedLogo.dds");
	m_LogoSprite->SetAlpha(m_LogoAlpha);

	m_PlayerHuntChoicesSprite = NewGO<SpriteRender>(0);
	m_PlayerHuntChoicesSprite->Init(L"PlayerDieChoices.dds");
	m_PlayerHuntChoicesSprite->SetAlpha(m_ChoicesAlpha);

	m_ChoicesIConSprite = NewGO<SpriteRender>(0);
	m_ChoicesIConSprite->Init(L"ChoicesIcon.dds");
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha);
	return true;
}

void HuntedSprite::Update()
{
	m_HuntAlpha += 0.01f;
	if (m_HuntAlpha >= 0.500f) {
		m_HuntAlpha = 0.500f;
		m_LogoAlpha += 0.01f;
	}
	if (m_LogoAlpha >= 1.000f) {
		m_LogoAlpha = 1.000f;
		m_ChoicesAlpha += 0.5f;
	}
	if (m_ChoicesAlpha >= 1.00f) {
		m_ChoicesAlpha = 1.000f;
	}
	m_HuntSprite->SetAlpha(m_HuntAlpha);
	m_LogoSprite->SetAlpha(m_LogoAlpha);
	m_PlayerHuntChoicesSprite->SetAlpha(m_ChoicesAlpha);
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha);
}

void HuntedSprite::OnDestroy()
{
	DeleteGO(m_HuntSprite);
	DeleteGO(m_LogoSprite);
	DeleteGO(m_PlayerHuntChoicesSprite);
	DeleteGO(m_ChoicesIConSprite);
}
