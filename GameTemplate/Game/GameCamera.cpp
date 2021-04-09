#include "pch.h"
#include "GameCamera.h"
#include "Player/Player.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	const float m_GameFar = 10000.0f;
	const float m_GameNear = 1.0f;
	m_player = FindGO<Player>("player");
	g_camera3D.SetFar(m_GameFar);
	g_camera3D.SetNear(m_GameNear);
	const float CharaConScele = 10.0f;
	m_CharaCon.Init(CharaConScele, CharaConScele, m_Pos);
	return true;
}

void GameCamera::Update()
{
	//カメラとプレイヤーの距離
	const CVector3 PlayerCameraLeave = { 0.0f,100.0f,500.0f };
	CVector3 PlayerPos= m_player->GetPosition();
	CVector3 Target = { PlayerPos.x,PlayerPos.y + m_player->GetHeight(),PlayerPos.z };
	g_camera3D.SetTarget(Target);
	CVector3 moveSpeed = CVector3::Zero();
	moveSpeed = PlayerCameraLeave;
	CQuaternion Rot = CQuaternion::Identity();
	//パッド入力の最小
	const float NotEntered = 0.001f;
	//パッドの入力がされていれば
	if (fabsf(g_pad[0].GetRStickXF()) > NotEntered) {
		//左右の回転量を調整
		const float XRotVolum = 2.0f;
		m_AngleX += g_pad[0].GetRStickXF()*XRotVolum;
	}
	Rot.SetRotationDeg(CVector3::AxisY(), -m_AngleX);
	Rot.Multiply(moveSpeed);
	//プレイヤーからちょっとカメラの終点に近い場所
	CVector3 RayStart = Target + moveSpeed * 0.01f;
	m_CharaCon.SetPosition(RayStart);
	//高さの回転量を調整
	const float YRotVolum = 20.0f;
	m_AngleY += g_pad[0].GetRStickYF()*YRotVolum;
	//高さの上限
	const float UpperLimit = 300.0f;
	//高さの下限
	const float LowerLimmit = -50.0f;
	if (m_AngleY < LowerLimmit) {
		m_AngleY = LowerLimmit;
	}
	if (m_AngleY > UpperLimit) {
		m_AngleY = UpperLimit;
	}
	//m_AngleY = max(LowerLimmit, min(UpperLimit, m_AngleY));
	moveSpeed.y += m_AngleY;
	//moveSpeed.y = max(LowerLimmit, min(UpperLimit, moveSpeed.y));
	if (moveSpeed.y < LowerLimmit) {
		moveSpeed.y = LowerLimmit;
	}
	if (moveSpeed.y > UpperLimit) {
		moveSpeed.y = UpperLimit;
	}
	const float deltaTime = 1.0f;
	m_Pos = m_CharaCon.Execute(deltaTime, moveSpeed);
	//m_Pos = Target + moveSpeed;
	g_camera3D.SetPosition(m_Pos);
	
	//カメラの更新。
	g_camera3D.Update();

	//ばねカメラのようなものを実装しようとしていた。
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
