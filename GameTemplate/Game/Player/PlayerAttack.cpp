#include "pch.h"
#include "PlayerAttack.h"
#include "Enemy/Enemy.h"
#include "Archer/Archer.h"
#include "Player/Player.h"
#include "Boss/Boss.h"

PlayerAttack::PlayerAttack()
{
}

PlayerAttack::~PlayerAttack()
{
}

bool PlayerAttack::Start()
{
	m_AttackModel = NewGO<SkinModelRender>(0);
	m_AttackModel->Init(L"DebugShere.cmo");
	m_AttackModel->SetPosition(m_Position);
	m_AttackModel->SetScale({ m_Aria, m_Aria, 1.0f });
	return true;
}

void PlayerAttack::Update()
{
	QueryGOs<Enemy>("enemy", [&](Enemy* enemy)->bool {
		CVector3 toEnemyPos = enemy->GetPosition() - m_Position;
		toEnemyPos.y = 0.0f;
		if (toEnemyPos.Length() < m_Aria) {
			if (!m_Hit) {
				enemy->HitDamage(m_Attack);
				m_Hit = true;
			}
		}
		return true;
	});
	QueryGOs<Archer>("archer", [&](Archer* archer)->bool {
		CVector3 toEnemyPos = archer->GetPosition() - m_Position;
		toEnemyPos.y = 0.0f;
		if (toEnemyPos.Length() < m_Aria) {
			if (!m_Hit) {
				archer->HitDamage(m_Attack);
				m_Hit = true;
			}
		}
		return true;
	});
	QueryGOs<Boss>("Boss", [&](Boss* boss)->bool {
		CVector3 toBossPos = boss->GetPosition() - m_Position;
		toBossPos.y = 0.0f;
		if (!m_Hit) {
			boss->HitDamage(m_Attack);
			m_Hit = true;
		}
		return true;
	});
}

void PlayerAttack::OnDestroy()
{
	DeleteGO(m_AttackModel);
}
