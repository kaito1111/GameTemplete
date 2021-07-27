#include "pch.h"
#include "PlayerAttack.h"
#include "Enemy/Enemy.h"
#include "Archer/Archer.h"
#include "Player/Player.h"
#include "Boss/Boss.h"

namespace {
}
PlayerAttack::PlayerAttack()
{
}

PlayerAttack::~PlayerAttack()
{
}

bool PlayerAttack::Start()
{
#ifdef _DEBUG
	m_AttackModel = NewGO<SkinModelRender>(0);
	m_AttackModel->Init(L"DebugShere.cmo");
	m_AttackModel->SetPosition(m_AttackPos);
	m_AttackModel->SetScale({ m_Aria, m_Aria, 1.0f });
#endif
	m_DamageSound.Init(L"PlayerAtack.wav");
	return true;
}

void PlayerAttack::Update()
{
	QueryGOs<Enemy>("enemy", [&](Enemy* enemy)->bool {
		CVector3 toEnemyPos = enemy->GetPosition() - m_AttackPos;
		toEnemyPos.y = 0.0f;
		if (toEnemyPos.Length() < m_Aria) {
			if (!m_Hit) {
				m_DamageSound.Play();
				enemy->HitDamage(m_Attack);
				m_Hit = true;
			}
		}
		return true;
	});
	QueryGOs<Archer>("archer", [&](Archer* archer)->bool {
		CVector3 toEnemyPos = archer->GetPosition() - m_AttackPos;
		toEnemyPos.y = 0.0f;
		if (toEnemyPos.Length() < m_Aria) {
			if (!m_Hit) {
				m_DamageSound.Play();
				archer->HitDamage(m_Attack);
				m_Hit = true;
			}
		}
		return true;
	});
	QueryGOs<Boss>("Boss", [&](Boss* boss)->bool {
		CVector3 toBossPos = boss->GetPosition() - m_AttackPos;
		toBossPos.y = 0.0f;
		if (toBossPos.Length() < m_Aria) {
			if (!m_Hit) {
				m_DamageSound.Play();
				boss->HitDamage(m_Attack);
	m_Hit = true;
			}
		}
		return true;
	});
}

void PlayerAttack::OnDestroy()
{
#ifdef _DEBUG
	DeleteGO(m_AttackModel);
#endif
}
