#include "pch.h"
#include "Character.h"

void Character::CharacterInit(wchar_t * filePath, float radius, float hight, const CVector3 & pos)
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(filePath);
	m_CharaCon.Init(radius, hight, pos);
}

void Character::Move(CVector3& move)
{
	Rotate();
	//当たり判定を実行
	m_ModelPos = m_CharaCon.Execute(gameTime().GetFrameDeltaTime(), move);
	//モデルの位置を設定
	m_Model->SetPosition(m_ModelPos);
	//モデルの回転を設定
	m_Model->SetRotation(m_ModelRot);
}

void Character::CharacterModelUpdate()
{
	m_Model->SetPosition(m_ModelPos);
	m_Model->SetRotation(m_ModelRot);
	m_Model->SetScale(m_ModelScale);
}

void Character::ForwardUpdate()
{
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_ModelRot);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_forward.Normalize();
}