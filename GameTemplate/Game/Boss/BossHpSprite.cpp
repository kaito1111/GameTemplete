#include "pch.h"
#include "BossHpSprite.h"

namespace {
	const float MaxHpScale = 0.98f;
}

bool BossHpSprite::Start()
{
	m_TopHpSprite = NewGO<SpriteRender>(1);
	m_TopHpSprite->Init(L"HP_Top_Red.dds", FRAME_BUFFER_W-100.0f, 90.0f);
	m_TopHpSprite->SetPosition(m_Pos);

	m_UnderHpSprite = NewGO<SpriteRender>(0);
	m_UnderHpSprite->Init(L"HP_Under_Brack.dds", FRAME_BUFFER_W- 100.0f, 120.0f);
	m_UnderHpSprite->SetPosition(m_Pos);

	m_MaxHp = m_Hp;
	return true;
}

void BossHpSprite::Update()
{
	CVector3 HpScale = CVector3::One();
	if (m_AppearanceHpScale < MaxHpScale) {
		m_AppearanceHpScale +=0.02f;
		HpScale.x = m_AppearanceHpScale;
	}
	else {
		HpScale.x = m_Hp / m_MaxHp;
		m_TopHpSprite->SetPivot({ SpriteRender::Right(), 0.5f });
		m_TopHpSprite->SetPosition({ -891.0f,-390.0f,0.0f });
	}
	m_TopHpSprite->SetScale(HpScale*MaxHpScale);
}

void BossHpSprite::OnDestroy()
{
	DeleteGO(m_TopHpSprite);
	DeleteGO(m_UnderHpSprite);
}
