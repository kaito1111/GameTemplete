#include "pch.h"
#include "Character.h"

void Character::Init(wchar_t * filePath, float radius, float hight, const CVector3 & pos)
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(filePath);
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Model->SetScale(m_Scale);
	m_CharaCon.Init(radius, hight, pos);
}

void Character::Move(CVector3& move)
{
	Rotate();
	//�����蔻������s
	m_Pos = m_CharaCon.Execute(gameTime().GetFrameDeltaTime(), move);
	//���f���̈ʒu��ݒ�
	m_Model->SetPosition(m_Pos);
	//���f���̉�]��ݒ�
	m_Model->SetRotation(m_Rot);
}