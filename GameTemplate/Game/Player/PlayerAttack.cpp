#include "pch.h"
#include "PlayerAttack.h"
#include "Enemy.h"
#include "Player/Player.h"

PlayerAttack::PlayerAttack()
{
}

PlayerAttack::~PlayerAttack()
{
}

bool PlayerAttack::Start()
{
	m_enemy = FindGO<Enemy>("enemy");
	return true;
}

void PlayerAttack::Update()
{
	QueryGOs<Enemy>("Enemy", [&](Enemy* enemy)->bool {
		CVector3 toEnemyPos = m_enemy->GetPosition() - m_Position;
		if (toEnemyPos.Length() < m_Aria) {
			m_enemy->Damege(m_damege);
		}
		if (m_AttackFrame < m_DeltaTime) {
			DeleteGO(this);
		}
		m_DeltaTime++;
		return true;
	});
}
