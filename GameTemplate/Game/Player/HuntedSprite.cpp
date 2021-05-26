#include "pch.h"
#include "HuntedSprite.h"
#include "ReSetGame.h"
#include "Fade.h"
#include "Title.h"

namespace {
	const float addSpriteAlpha = 0.05f;
	const float priority = 1;
	const float RestarPos = -100.0f;
	const float TitlePos = -350.0f;
}
bool HuntedSprite::Start()
{
	m_HuntSprite = NewGO<SpriteRender>(priority);
	m_HuntSprite->Init(L"PlayerHunted.dds");
	m_HuntSprite->SetAlpha(m_HuntAlpha);
	//ロゴはDieスプライトより手前に来てほしいので-１する
	m_LogoSprite = NewGO<SpriteRender>(priority -1);
	m_LogoSprite->Init(L"PlayerHuntedLogo.dds");
	m_LogoSprite->SetAlpha(m_LogoAlpha);

	m_ChoicesIConSprite = NewGO<SpriteRender>(priority - 1);
	m_ChoicesIConSprite->Init(L"ChoicesIcon.dds");
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha);
	m_IConPos.y = RestarPos;
	m_ChoicesIConSprite->SetPosition(m_IConPos);
	return true;
}

void HuntedSprite::Update()
{
	m_HuntAlpha += addSpriteAlpha;
	if (m_HuntAlpha >= 0.500f) {
		m_HuntAlpha = 0.500f;
		m_LogoAlpha += addSpriteAlpha;
	}
	if (m_LogoAlpha >= 1.000f) {
		m_LogoAlpha = 1.000f;
		m_ChoicesAlpha += 0.5f;
	}
	if (m_ChoicesAlpha >= 1.00f) {
		m_ChoicesAlpha = 1.000f;
	}
	//リスタートが選ばれると
	if (m_IConPos.y >= RestarPos &&
		g_pad[0].IsPress(enButtonA)&&
		m_fade==nullptr) {
		m_fade = NewGO<Fade>(0);
		ReSetGame* reGame = NewGO<ReSetGame>(0, "resetGame");
		reGame->SetFade(m_fade);
	}
	//タイトルが選ばれると
	if (m_IConPos.y >= TitlePos &&
		g_pad[0].IsPress(enButtonA)) {

	}
	if (m_fade != nullptr) {
		if (m_fade->GetAlpha() > 0.9f) {
			DeleteGO(this);
		}
	}
	if (g_pad[0].GetLStickYF() > 0.9f) {
		m_IConPos.y = RestarPos;
	}
	if (g_pad[0].GetLStickYF() < -0.9f) {
		m_IConPos.y = TitlePos;
	}
	m_ChoicesIConSprite->SetPosition(m_IConPos);
	m_HuntSprite->SetAlpha(m_HuntAlpha);
	m_LogoSprite->SetAlpha(m_LogoAlpha);
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha);
}

void HuntedSprite::OnDestroy()
{
	DeleteGO(m_HuntSprite);
	DeleteGO(m_LogoSprite);
	DeleteGO(m_ChoicesIConSprite);
}
