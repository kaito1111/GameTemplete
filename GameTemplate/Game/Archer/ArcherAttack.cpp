#include "pch.h"
#include "ArcherAttack.h"
#include "Player/Player.h"

namespace {
	const float Aria = 30.0f;
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

	m_DrawSound.Init(L"DamageArrow.wav");
	return true;
}

void ArcherAttack::Update()
{
	m_Position.y = 0;
	CVector3 Diff = m_Position - m_Player->GetPosition();
	if (Diff.Length() < Aria) {
		if (m_Player->GetState() < Player::State::Damage&&
			m_Player->GetState() < Player::State::Roling&&
			m_Player->GetState() < Player::State::GameClear) {
			m_DrawSound.Play();
			m_Player->HitDamage(Damage);
		}
	}
	m_Model->SetPosition(m_Position);
}
