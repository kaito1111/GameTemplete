#include "pch.h"
#include "BossWalkState.h"

void BossWalkState::Update()
{
	m_Boss->PlayAnimation();
	CVector3 MoveSpeed = m_Boss->GetPlayerPos() - m_Boss->GetPosition();
	MoveSpeed.Normalize();
	MoveSpeed *= 5.0f;
	m_Boss->Move(MoveSpeed);
	m_Boss->IsChengeNormalRoar();
	m_Boss->IsChengeAttackState();
}
