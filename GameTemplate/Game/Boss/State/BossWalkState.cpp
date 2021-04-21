#include "pch.h"
#include "BossWalkState.h"

void BossWalkState::Update()
{
	m_Boss->PlayAnimation();
	m_Boss->IsChengeNormalRoar();
	m_Boss->IsChengeAttackState();
}
