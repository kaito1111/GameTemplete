#include "pch.h"
#include "BossAttackState.h"

void BossAttackState::Update()
{
	m_Boss->PlayAnimation(1.75f);
	if (!m_Boss->IsPlayAnimation())
	{
		m_Boss->SetWalkState();
		m_Boss->IsChengeNormalRoar();
	}
}
