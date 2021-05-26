#include "pch.h"
#include "DieSprite.h"

namespace {
	float addSpriteAlpha = 0.01f;
	float priority = 5;
}

bool DieSprite::Start()
{
	m_DieSprite = NewGO<SpriteRender>(priority);
	m_DieSprite->Init(L"PlayerDie.dds");
	m_DieSprite->SetAlpha(m_DieAlpha);
	//ロゴはDieスプライトより手前に来てほしいので＋１する
	m_LogoSprite = NewGO<SpriteRender>(priority+1);
	m_LogoSprite->Init(L"PlayerDieLogo.dds");
	m_LogoSprite->SetAlpha(m_LogoAlpha);

	m_PlayerDieChoicesSprite = NewGO<SpriteRender>(priority + 1);
	m_PlayerDieChoicesSprite->Init(L"PlayerDieChoices.dds");
	m_PlayerDieChoicesSprite->SetAlpha(m_ChoicesAlpha);

	m_ChoicesIConSprite = NewGO<SpriteRender>(priority + 1);
	m_ChoicesIConSprite->Init(L"ChoicesIcon.dds");
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha);
	return true;
}

void DieSprite::Update()
{
	m_DieAlpha += 0.01f;
	if (m_DieAlpha >= 0.500f) {
		m_DieAlpha = 0.500f;
		m_LogoAlpha += 0.01f;
	}
	if (m_LogoAlpha >= 1.000f) {
		m_LogoAlpha = 1.000f;
		m_ChoicesAlpha += 0.5f;
	}
	if (m_ChoicesAlpha >= 1.00f) {
		m_ChoicesAlpha = 1.000f;
	}
	m_DieSprite->SetAlpha(m_DieAlpha);
	m_LogoSprite->SetAlpha(m_LogoAlpha);
	m_PlayerDieChoicesSprite->SetAlpha(m_ChoicesAlpha);
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha);
}

void DieSprite::OnDestroy()
{
	DeleteGO(m_DieSprite);
	DeleteGO(m_LogoSprite);
	DeleteGO(m_PlayerDieChoicesSprite);
	DeleteGO(m_ChoicesIConSprite);
}
