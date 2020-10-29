#include "pch.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	g_camera3D.SetFar(2000.0f);
	g_camera3D.SetNear(1.0f);
	m_CharaCon.Init(10.0f, 10.0f, m_Pos);
	return true;
}

void GameCamera::Update()
{
	CVector3 Target = m_player->GetPosition();
	g_camera3D.SetTarget(Target);
	m_Pos = { 0.0f,100.0f,500.0f };
	CQuaternion Rot = CQuaternion::Identity();
	if (fabsf(g_pad[0].GetRStickXF()) > 0.001f) {
		m_AngleX += g_pad[0].GetRStickXF()*2.0f;
	}
	Rot.SetRotationDeg(CVector3::AxisY(), -m_AngleX);
	Rot.Multiply(m_Pos);
	m_AngleY += g_pad[0].GetRStickYF()*20.0f;
	m_AngleY = max(-50.0f, min(300.0f, m_AngleY));
	m_Pos.y += m_AngleY;
	m_Pos.y = max(-50.0f, min(300.0f, m_Pos.y));
	m_Pos += Target;
	g_camera3D.SetPosition(m_Pos);

	//‚Î‚ËƒJƒƒ‰‚Ì‚æ‚¤‚È‚à‚Ì‚ðŽÀ‘•‚µ‚æ‚¤‚Æ‚µ‚Ä‚¢‚½B
	//CVector3 Target = m_player->GetPosition();
	//g_camera3D.SetTarget(Target);
	//CVector3 StartCameraPos = { 0.0f,100.0f,500.0f };
	//StartCameraPos += Target;
	//m_CharaCon.SetPosition(StartCameraPos);
	//CVector3 MoveSpeed;
	//CQuaternion Rot = CQuaternion::Identity();
	//if (fabsf(g_pad[0].GetRStickXF()) > 0.001f) {
	//	m_AngleX += g_pad[0].GetRStickXF()*2.0f;
	//}
	//Rot.SetRotationDeg(CVector3::AxisY(), -m_AngleX);
	//Rot.Multiply(MoveSpeed);
	//m_AngleY += g_pad[0].GetRStickYF()*20.0f;
	//m_AngleY = max(-100.0f, min(300.0f, m_AngleY));
	//MoveSpeed.y += m_AngleY;
	//MoveSpeed.y = max(-100.0f, min(300.0f, MoveSpeed.y));
	//MoveSpeed += Target;
	//m_Pos = m_CharaCon.Execute(1.0f, MoveSpeed);
	//g_camera3D.SetPosition(m_Pos);
}
