#include "pch.h"
#include "ArcherAttack.h"
#include "Player/Player.h"

namespace {
	const float Aria = 50.0f;
	const float Damage = 10.0f;
}

ArcherAttack::~ArcherAttack()
{
	DeleteGO(m_Model);
}

bool ArcherAttack::Start()
{
	m_Model = NewGO<SkinModelRender>(0); 
	m_Model->Init(L"DebugShere.cmo");
	m_Model->SetPosition(m_Position);
	CVector3 scale = { Aria,Aria,1.0f };
	m_Model->SetScale(scale);

	m_Player = FindGO<Player>("player");
	return true;
}

void ArcherAttack::Update()
{
	m_Position.y = 0;
	CVector3 Diff = m_Position - m_Player->GetPosition();
	if (Diff.Length() < Aria) {
		if (m_Player->GetMutekiFlame() < 0) {
			m_Player->HitDamage(Damage);
		}
	}
	m_Model->SetPosition(m_Position);
}
