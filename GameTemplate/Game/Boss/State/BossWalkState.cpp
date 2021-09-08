#include "pch.h"
#include "BossWalkState.h"

void BossWalkState::Update()
{
	m_Boss->PlayAnimation(0.6f);
	m_Boss->AIWalk();
	m_Boss->IsChengeNormalRoar();
	m_Boss->IsChengeAttackState();
}
