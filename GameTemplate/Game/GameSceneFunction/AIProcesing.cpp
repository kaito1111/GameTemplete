#include "pch.h"
#include "AIProcesing.h"
#include "Attack.h"

namespace {
	const int AttackPrio = 0;
	const float MoveSpeed = 2.3f;
} 

void AIProcesing::AIAttack(float damage,float eria,char* AttackName)
{
	CVector3 AttackPos = m_ModelPos + m_forward * AttackReach;
	m_HaveAttack = NewGO<Attack>(AttackPrio, AttackName);
	m_HaveAttack->Init(damage, eria, AttackPos);
}

AIProcesing::~AIProcesing()
{
	if (m_HaveAttack != nullptr) {
		DeleteGO(m_HaveAttack);
	}
}

void AIProcesing::AIWalk()
{
	m_MoveSpeed = m_player->GetPosition() - m_ModelPos;
	m_MoveSpeed.Normalize();
	m_MoveSpeed *= MoveSpeed;
	Move(m_MoveSpeed);
}