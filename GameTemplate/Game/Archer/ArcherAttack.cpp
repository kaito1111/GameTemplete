#include "pch.h"
#include "ArcherAttack.h"
#include "Player/Player.h"

ArcherAttack::~ArcherAttack()
{
	DeleteGO(m_Model);
}

bool ArcherAttack::Start()
{
	m_Model = NewGO<SkinModelRender>(0); 
	m_Model->Init(L"Assets/modelData/DebugShere.cmo");
	m_Model->SetPosition(m_Position);
	CVector3 scale = { 1.0f,1.0f,0.0f };
	m_Model->SetScale(scale);

	m_Player = FindGO<Player>("player");
	return true;
}

void ArcherAttack::Update()
{
	CVector3 Diff = m_Position - m_Player->GetPosition();
	if (Diff.Length() < 100.0f) {
		m_Player->HitDamage(30.0f);
	}
}
