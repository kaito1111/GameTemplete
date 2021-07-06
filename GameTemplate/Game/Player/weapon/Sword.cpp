#include "pch.h"
#include "Sword.h"

void Sword::Start()
{
	m_model = NewGO<SkinModelRender>(0);
	m_model->Init(L"PlayerSword.cmo");
	m_model->SetPosition(m_Position);
}

void Sword::Update()
{
	m_model->SetPosition(m_Position);
	m_model->SetRotation(m_Rotation);
}
