#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	m_model = NewGO<SkinModelRender>(0);
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/unityChan.cmo");
	m_model->SetPosition(m_Pos);
	m_model->SetRotation(m_Rot);
	m_CharaCon.Init(20.0f, 80.0f,m_Pos);
	return true;
}

void Player::Update()
{
	CVector3 m_MoveSpeed = CVector3::Zero();
	m_MoveSpeed.x -= g_pad[0].GetLStickXF()*20.0f;
	//g_physics.
	m_Pos = m_CharaCon.Execute(1 / 60.0, m_MoveSpeed);
	m_model->SetPosition(m_Pos);
	m_angle = atan2(g_pad[0].GetLStickXF(), g_pad[0].GetLStickYF());
	m_Rot.SetRotationDeg(CVector3::AxisY(), m_angle);
	m_model->SetRotation(m_Rot);
}