#include "pch.h"
#include "BossHpSprite.h"

namespace {
	float SpriteScaleSub = 600.0f;//HP�o�[��S�̂��牽�Z���`������
	float SpriteHight = 25.0f;
	float HpAddMax = 0.02f;
}

bool BossHpSprite::Start()
{
	m_TopHpSprite = NewGO<SpriteRender>(1);
	m_TopHpSprite->Init(L"HP_Top_Red.dds", FRAME_BUFFER_W - SpriteScaleSub, SpriteHight);
	m_TopHpSprite->SetPosition(m_Pos);
	m_TopHpSprite->SetPivot({ SpriteRender::Right(), 0.5f });
	m_HpScale.x = 0.0f;
	m_TopHpSprite->SetScale(m_HpScale);
	m_UnderHpSprite = NewGO<SpriteRender>(0);
	m_UnderHpSprite->Init(L"HP_Under_Brack.dds", FRAME_BUFFER_W - SpriteScaleSub, SpriteHight);
	m_UnderHpSprite->SetPosition(m_Pos);
	m_UnderHpSprite->SetPivot({ SpriteRender::Right(), 0.5f });

	m_HpTopTranslucentSprite = NewGO<SpriteRender>(0);
	m_HpTopTranslucentSprite->Init(L"HP_Top_Red.dds", FRAME_BUFFER_W - SpriteScaleSub, SpriteHight);
	//��������
	m_HpTopTranslucentSprite->SetAlpha(0.5f);
	//��ԏ��Hp�Ƒ傫�������킹��
	m_HpTopTranslucentSprite->SetScale(m_HpScale);
	m_HpTopTranslucentSprite->SetPivot({ SpriteRender::Right(), 0.5f });
	m_HpTopTranslucentSprite->SetPosition(m_Pos);

	m_MaxHp = m_Hp;
	return true;
}

void BossHpSprite::Update()
{
	float HpRatio = m_Hp / m_MaxHp;
	//����������Hp�������Ă���悤�Ɍ�����
	float addHpRatio = min(HpAddMax, HpRatio);


	m_HpScale.x += addHpRatio;
	//Hp�̊����ȏ�ɂ͂��Ȃ�
	m_HpScale.x = min(m_HpScale.x, HpRatio);
	if (m_HpScale.x >= HpRatio) {
		if (!m_HpInit) {
			m_TranslunceSpriteScale = m_HpScale; 
			m_TranslucentScale = HpRatio;
		}
		//Hp�̊�����Hp�����ȉ��Ȃ̂ŏ������ł��������ɂ���
		m_HpInit = true;
	}
	m_TopHpSprite->SetScale(m_HpScale);
	if (m_HpInit) {
		float diff = fabsf(m_TranslunceSpriteScale.x - m_HpScale.x);
		if (diff > 0.01f) {
			m_HoldTime -= gameTime().GetFrameDeltaTime();
		}
		if (m_HoldTime < 0.0f) {
			m_TranslucentScale -= 0.005f;
		}
		if (diff <= 0.01f) {
			m_HoldTime = 1.0f;
		}
		m_TranslunceSpriteScale.x = m_TranslucentScale;
		m_HpTopTranslucentSprite->SetScale(m_TranslunceSpriteScale);
	}
	if (m_Hp <= 0.0f) {
		m_HpTopTranslucentSprite->SetAlpha(0.0f);
	}
}

void BossHpSprite::OnDestroy()
{
	DeleteGO(m_TopHpSprite);
	DeleteGO(m_UnderHpSprite);
}
