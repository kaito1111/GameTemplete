#include "pch.h"
#include "DieSprite.h"
#include "fade.h"
#include "ReSetGame.h"
#include "ReSetTitle.h"

namespace {
	float addSpriteAlpha = 0.01f;
	float priority = 5;
	const float RestarPos = 50.0f;
	const float TitlePos = -200.0f;
}

bool DieSprite::Start()
{
	m_DieSprite = NewGO<SpriteRender>(priority);
	m_DieSprite->Init(L"PlayerDie.dds");
	m_DieSprite->SetAlpha(m_DieAlpha);
	//ロゴはDieスプライトより手前に来てほしいので＋１する
	m_LogoSprite = NewGO<SpriteRender>(priority+1);
	m_LogoSprite->Init(L"PlayerDieLogo.dds", 1280.0f, 920.0f);
	m_LogoSprite->SetAlpha(m_LogoAlpha);

	m_PlayerDieChoicesSprite = NewGO<SpriteRender>(priority + 1);
	m_PlayerDieChoicesSprite->Init(L"PlayerDieChoices.dds",1280.0f,920.0f);
	m_PlayerDieChoicesSprite->SetAlpha(m_ChoicesAlpha);

	m_ChoicesIConSprite = NewGO<SpriteRender>(priority + 1);
	m_ChoicesIConSprite->Init(L"ChoicesIcon.dds",1280.0f, 920.0f);
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha);
	m_ChoicesIConSprite->SetPosition(m_IConPos);
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
	if (m_ChoicesAlpha >= 1.00f) {
		//リスタートが選ばれると
		if (m_IConPos.y >= RestarPos &&
			g_pad[0].IsPress(enButtonA) &&
			IsReset == false) {
			ReSetGame* reGame = NewGO<ReSetGame>(0, "resetGame");
			IsReset = true;
		}
		//タイトルが選ばれると
		if (m_IConPos.y >= TitlePos &&
			g_pad[0].IsPress(enButtonA) &&
			IsReset == false) {
			ReSetTitle* m_Title = NewGO<ReSetTitle>(0, "resettitle");
			IsReset = true;
		}
	}
	if (g_pad[0].GetLStickYF() > 0.9f) {
		m_IConPos.y = RestarPos;
	}
	if (g_pad[0].GetLStickYF() < -0.9f) {
		m_IConPos.y = TitlePos;
	}
	m_DieSprite->SetAlpha(m_DieAlpha);
	m_LogoSprite->SetAlpha(m_LogoAlpha);
	m_PlayerDieChoicesSprite->SetAlpha(m_ChoicesAlpha);
	m_ChoicesIConSprite->SetAlpha(m_ChoicesAlpha); 
	m_ChoicesIConSprite->SetPosition(m_IConPos);
}

void DieSprite::OnDestroy()
{
	DeleteGO(m_DieSprite);
	DeleteGO(m_LogoSprite);
	DeleteGO(m_PlayerDieChoicesSprite);
	DeleteGO(m_ChoicesIConSprite);
}
