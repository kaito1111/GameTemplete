#include "pch.h"
#include "PlayerAttack.h"
#include "Enemy/Enemy.h"
#include "Player/Player.h"

PlayerAttack::PlayerAttack()
{
}

PlayerAttack::~PlayerAttack()
{
}

bool PlayerAttack::Start()
{
	return true;
}

void PlayerAttack::Update()
{
	QueryGOs<Enemy>("enemy", [&](Enemy* enemy)->bool {
		CVector3 toEnemyPos = enemy->GetPosition() - m_Position;
		toEnemyPos.y = 0.0f;
		if (toEnemyPos.Length() < m_Aria) {
			if (!enemy->IsMuteki()) {
				enemy->HitDamege(m_Attack);
			}
		}
		if (m_AttackFrame < m_DeltaTime) {
			DeleteGO(this);
		}
		m_DeltaTime++;
		return true;
	});
}
