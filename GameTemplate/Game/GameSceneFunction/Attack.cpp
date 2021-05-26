#include "pch.h"
#include "Attack.h"
#include "Player/Player.h"

void Attack::Update()
{
	CVector3 toPlayerPos = m_Player->GetPosition() - m_Position;
	if (toPlayerPos.Length() < m_Area) {
		if (m_Player->GetState() < Player::State::Damage&&
			m_Player->GetState() < Player::State::Roling&&
			m_Player->GetState() < Player::State::GameClear) {
			m_Player->HitDamage(m_Damege);
		}
	}
}

void Attack::OnDestroy()
{
	DeleteGO(m_AttackModel);
}
