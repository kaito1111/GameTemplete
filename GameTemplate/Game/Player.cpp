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
	m_model->Init(L"Assets/modelData/Player.cmo");
	m_model->SetPosition(m_Pos);
	m_model->SetRotation(m_Rot);
	m_CharaCon.Init(20.0f, 80.0f,m_Pos);
	return true;
}

void Player::Update()
{
	CVector3 MoveSpeed = CVector3::Zero();
	MoveSpeed.x -= g_pad[0].GetLStickXF();
	MoveSpeed.z += g_pad[0].GetLStickYF();
	if (fabsf(MoveSpeed.Length()) > 0.1f) { 
		MoveSpeed *= 20.0f;
	}
	m_Pos = m_CharaCon.Execute(1 / 60.0, MoveSpeed);
	m_model->SetPosition(m_Pos);

	CVector3 MoveDir = { g_pad[0].GetLStickXF(),0.0f,g_pad[0].GetLStickYF() };

	m_angle = atan2(MoveDir.x, MoveDir.z);

	m_Rot.SetRotation(CVector3::AxisY(), -m_angle);
	//m_Rot.Multiply(m_Forward);
	m_model->SetRotation(m_Rot);
}