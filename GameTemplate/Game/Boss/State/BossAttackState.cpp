#include "pch.h"
#include "BossAttackState.h"

void BossAttackState::Update()
{
	m_Boss->PlayAnimation();
	m_Boss->SetWalkState();
}
