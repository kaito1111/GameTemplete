#include "pch.h"
#include "BossNormalRoar.h"

void BossNormalRoar::Update()
{
	m_Boss->PlayAnimation(0.7f);
	if (!m_Boss->IsPlayAnimation()) {
		m_Boss->SetWalkState();
	}
}
