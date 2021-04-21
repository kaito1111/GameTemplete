#include "pch.h"
#include "BossWalkState.h"

void BossWalkState::Update()
{
	m_Boss->PlayAnimation();
}
