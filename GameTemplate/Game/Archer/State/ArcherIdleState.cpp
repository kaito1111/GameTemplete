#include "pch.h"
#include "ArcherIdleState.h"

void ArcherIdleState::Update()
{
	m_Archer->TryAttackState();
}
