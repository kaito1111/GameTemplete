#include "pch.h"
#include "Enemy.h"
#include "Player/Player.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"Assets/modelData/keleton.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetRotation(m_Rot);
	m_Skin->SetScale(m_Scale);
	m_Skin->SetRenderMode(1);
	m_CharaCon.Init(20.0f, m_height, m_Pos);
	m_HpTopSprite = NewGO<SpriteRender>(2);
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_Hp, 10.0f, true);
	m_HpPosition = m_Pos;
	m_HpPosition.y += m_height + 10.0f;
	m_HpTopSprite->SetPosition(m_HpPosition);
	//m_HpTopSprite->SetPivot({ -1.0f,0.0f });
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, 10.0f, true);
	m_HpUnderSprite->SetPosition(m_HpPosition);

	m_AniClip[AnmePattern::Walk].Load(L"Assets/AnimData/SkeltonWalk.tka");
	m_AniClip[AnmePattern::Attack].Load(L"Assets/AnimData/SkeltonAttack.tka");
	m_AniClip[AnmePattern::Damage].Load(L"Assets/AnimData/SkeltonDamage.tka");
	m_Animation.Init(m_Skin->GetModel(), m_AniClip, AnmePattern::Num);
	
	return true;
}
void Enemy::OnAnimEvent(const wchar_t* eventName)
{
	if (wcscmp(eventName, L"AttackEnd1") == 0) {
		m_AttackPattarn = 1;

	}
	if (wcscmp(eventName, L"AttackEnd2") == 0) {
		m_AttackPattarn = 0;
	}
}

void Enemy::Update()
{
	m_MoveSpeed = m_Player->GetPosition()- m_Pos;
	m_MoveSpeed.Normalize();
	m_MoveSpeed *= 5.0f;
	m_Pos = m_CharaCon.Execute(1.0f / 60.0f, m_MoveSpeed);
	UpdateSprite();
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetRotation(m_Rot);
	if (m_AttackPattarn == 1) {
		m_EnemyAttack = NewGO<EnemyAttack>(0);
		m_EnemyAttack->Init(20.0f, 20.0f,m_Pos,0.0f);
	}
	if (g_pad[0].IsPress(enButtonA)) {
		m_Animation.Play(AnmePattern::Attack);
	}
	if (g_pad[0].IsPress(enButtonB)) {
		m_Animation.Play(AnmePattern::Walk);
	}
	if (g_pad[0].IsPress(enButtonX)) {
		m_Animation.Play(AnmePattern::Damage);
	}

	m_Animation.Update(1.0f / 60.0f);
}

void Enemy::EnemyRot()
{
	CVector3 diff = m_Player->GetPosition() - m_Pos;
	float angle = atan2(diff.x, diff.z);
	m_Rot.SetRotation(CVector3::AxisY(), angle);
}

void Enemy::UpdateSprite()
{
	m_HpPosition = m_Pos;
	m_HpPosition.y += m_height +10.0f;
	float SizeX = m_Hp * m_SpriteSize;
	m_HpTopSprite->SetScale({ SizeX,1.0f,1.0f });
	m_HpTopSprite->SetPosition(m_HpPosition);
	m_HpUnderSprite->SetPosition(m_HpPosition);
}