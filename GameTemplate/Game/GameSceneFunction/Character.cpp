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
	//当たり判定を実行
	m_Pos = m_CharaCon.Execute(gameTime().GetFrameDeltaTime(), move);
	//モデルの位置を設定
	m_Model->SetPosition(m_Pos);
	//モデルの回転を設定
	m_Model->SetRotation(m_Rot);
}