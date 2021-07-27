#include "pch.h"
#include "BossNormalRoar.h"

void BossNormalRoar::Update()
{
	m_Boss->PlayAnimation(1.5f);
	if (!m_Boss->IsPlayAnimation()) {
		m_Boss->SetWalkState();
	}
}
