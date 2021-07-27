#include "pch.h"
#include "AIProcesing.h"
#include "Attack.h"

namespace {
	const int AttackPrio = 0;		//攻撃の優先順位
	const float MoveSpeed = 2.3f;	//移動できる距離
	const float MaxApperDiff = 400.0f;//HPを視認できる最大の距離
	const float DeleteTime = 1.5f;	//Hpスプライトが見えなくなってから消えるまでの時間
} 

void AIProcesing::AIAttack(float damage,float eria,char* AttackName)
{
	CVector3 AttackPos = m_ModelPos + m_forward * AttackReach;
	m_HaveAttack = NewGO<Attack>(AttackPrio, AttackName);
	m_HaveAttack->Init(damage, eria, AttackPos);
}

void AIProcesing::UpdateHpAlpha()
{
	if (m_Hp <= 0) {
		m_HpTopSprite->SetActiveFlag(false);
		m_HpTopTranslucentSprite->SetActiveFlag(false);
		m_HpUnderSprite->SetActiveFlag(false);
		return;
	}
	CVector3 Diff = m_player->GetPosition() - m_ModelPos;
	float Dis = MaxApperDiff - Diff.Length();
	float NextHpAlhpa = 0.0f;
	if (Diff.Length() < MaxApperDiff) {
		m_HpAlhpa += 0.3f;
		m_deltaTime = 0.0f;
	}
	else {
		m_deltaTime += gameTime().GetFrameDeltaTime();
	}
	if (m_deltaTime >=DeleteTime) {
		m_HpAlhpa -= 0.05f;
	}
	m_HpAlhpa = min(m_HpAlhpa, 1.0f);
	m_HpAlhpa = max(m_HpAlhpa, 0.0f);
	m_HpTopSprite->SetAlpha(m_HpAlhpa);
	m_HpTopTranslucentSprite->SetAlpha(m_HpAlhpa*0.5f);
	m_HpUnderSprite->SetAlpha(m_HpAlhpa);
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