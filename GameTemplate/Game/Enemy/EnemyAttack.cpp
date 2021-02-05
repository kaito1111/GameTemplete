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
	return true;
}

void EnemyAttack::Update()
{
	CVector3 toPlayerPos =	m_Player->GetPosition()- m_Position;
	if (toPlayerPos.Length()>m_Area) {
		m_Player->HitDamage(m_Damege);
	}
	if (m_AttackFrame < m_deltaFrame) {
		DeleteGO(this);
	}
	m_deltaFrame++;
}