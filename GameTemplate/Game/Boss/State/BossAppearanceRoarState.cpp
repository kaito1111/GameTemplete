#include "pch.h"
#include "BossAppearanceRoarState.h"

void BossAppearanceRoarState::Update()
{
	m_Boss->PlayAnimation();
	if (!m_Boss->IsPlayAnimation()) {
		m_Boss->SetWalkState();
	}
}
