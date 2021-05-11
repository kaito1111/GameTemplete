#include "pch.h"
#include "AIProcesing.h"
#include "Attack.h"

void AIProcesing::AIAttack(float damage,float eria,char* AttackName)
{

	CVector3 AttackPos = m_ModelPos + m_forward * AttackReach;
	m_HaveAttack = NewGO<Attack>(0, AttackName);
	m_HaveAttack->Init(damage, eria, AttackPos);
}

void AIProcesing::AIWalk()
{
	m_MoveSpeed = m_player->GetPosition() - m_ModelPos;
	m_MoveSpeed.Normalize();
	m_MoveSpeed *= 100.0f;
	Move(m_MoveSpeed);
}