#include "pch.h"
#include "ArcherAttackState.h"
#include "Archer/Archer.h"

void ArcherAttackState::Update()
{

	if (!m_Archer->IsPlayAnimation()) {
		m_Archer->SetIdleState();
	}
}
