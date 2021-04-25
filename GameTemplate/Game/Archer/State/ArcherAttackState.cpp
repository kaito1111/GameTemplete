#include "pch.h"
#include "ArcherAttackState.h"
#include "Archer/Archer.h"

void ArcherAttackState::Update()
{
	if (m_Archer->IsFacingFlag()) {
		m_Archer->Rotate();
	}
	if (!m_Archer->IsPlayAnimation()) {
		m_Archer->SetFacingFlag();
		m_Archer->SetIdleState();
	}
}
