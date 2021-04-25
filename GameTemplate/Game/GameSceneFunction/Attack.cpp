#include "pch.h"
#include "Attack.h"
#include "Player/Player.h"

void Attack::Update()
{
	CVector3 toPlayerPos = m_Player->GetPosition() - m_Position;
	if (toPlayerPos.Length() < m_Area) {
		if (m_Player->GetMutekiFlame() < 0) {
			m_Player->HitDamage(m_Damege);
		}
	}
}
