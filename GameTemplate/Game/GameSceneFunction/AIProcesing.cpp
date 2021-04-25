#include "pch.h"
#include "AIProcesing.h"
#include "Attack.h"

void AIProcesing::AIAttack(float damage,float eria,char* AttackName)
{
	//UŒ‚‚ÌŒ¨‚©‚ç˜r‚Ü‚Å‚Ì‹——£
	const float AttackReach = 100.0f;
	CVector3 AttackPos = m_Pos + m_forward * AttackReach;
	Attack* attack=	NewGO<Attack>(0, AttackName);
	attack->Init(damage, eria, AttackPos);
}

void AIProcesing::AIWalk()
{
	CVector3 MoveSpeed = m_player->GetPosition() - m_Pos;
	MoveSpeed.Normalize();
	MoveSpeed *= 100.0f;
	Move(MoveSpeed);
}