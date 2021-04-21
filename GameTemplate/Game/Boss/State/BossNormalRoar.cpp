#include "pch.h"
#include "BossNormalRoar.h"

void BossNormalRoar::Update()
{
	m_Boss->PlayAnimation();
	if (!m_Boss->IsPlayAnimation()) {
		m_Boss->SetWalkState();
	}
}
