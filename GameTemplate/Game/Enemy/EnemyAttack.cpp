#include "pch.h"
#include "EnemyAttack.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"

EnemyAttack::EnemyAttack()
{
}

EnemyAttack::~EnemyAttack()
{
}

bool EnemyAttack::Start()
{
	m_Player = FindGO<Player>("player");
	m_AttackModel = NewGO<SkinModelRender>(0);
	m_AttackModel->Init(L"DebugShere.cmo");
	m_AttackModel->SetPosition(m_Position);
	CVector3 ModelScale = { m_Area,m_Area,1.0f };
	m_AttackModel->SetScale(ModelScale);
	return true;
}

void EnemyAttack::Update()
{
	CVector3 toPlayerPos =	m_Player->GetPosition()- m_Position;
	if (toPlayerPos.Length()<m_Area) {
		if (m_Player->GetMutekiFlame() < 0) {
			m_Player->HitDamage(m_Damege);
		}
	}
}

void EnemyAttack::OnDestroy()
{
	DeleteGO(m_AttackModel);
}
