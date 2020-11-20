#include "pch.h"
#include "Enemy.h"
#include "Player/Player.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Hit()
{
	CVector3 diff = m_Pos - m_Player->GetPosition();
	CVector3 Right = CVector3::Right(); 
	diff.Normalize();
	Right.Cross(diff, CVector3::Up());
	m_DownAngle = 10.0f;
	CQuaternion DownRot;
	DownRot.SetRotationDeg(Right, m_DownAngle);
	m_Rot.Multiply(DownRot);
}

bool Enemy::Start()
{
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"Assets/modelData/Enemy.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetRotation(m_Rot);
	m_Skin->SetScale(m_Scale);
	m_CharaCon.Init(20.0f, 30.0f, m_Pos);
	//m_DownModel = NewGO<SkinModelRender>(0);
	//m_DownModel->Init(L"")
	return true;
}

void Enemy::Update()
{
	CVector3 HitDiff = m_Pos - m_Player->AttackPos();
	EnemyRot();
	if (g_pad[0].IsPress(enButtonX)) {
		if (HitDiff.Length() < 40.0f) {
			Hit();
		}
	}
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetRotation(m_Rot);
}

void Enemy::EnemyRot()
{
	CVector3 diff = m_Player->GetPosition() - m_Pos;
	float angle = atan2(diff.x, diff.z);
	m_Rot.SetRotation(CVector3::AxisY(), angle);
}
