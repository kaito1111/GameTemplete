#include "pch.h"
#include "BossAttackState.h"

void BossAttackState::Update()
{
	m_Boss->PlayAnimation();
	if (!m_Boss->IsPlayAnimation())
	{
		m_Boss->SetWalkState();
		m_Boss->IsChengeNormalRoar();
	}
}
