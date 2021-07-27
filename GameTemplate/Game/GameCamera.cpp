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
	const float m_GameFar = 15000.0f;
	const float m_GameNear = 1.0f;
	m_player = FindGO<Player>("player");
	g_camera3D.SetFar(m_GameFar);
	g_camera3D.SetNear(m_GameNear);
	const float CharaConScele = 10.0f;
	m_CharaCon.Init(CharaConScele, CharaConScele, m_Pos);
	CQuaternion ReverceRot = CQuaternion::Identity();
	ReverceRot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_StartRot.Multiply(ReverceRot);
	return true;
}

void GameCamera::Update()
{
	if (m_player != nullptr) {
		CVector3 PlayerPos = m_player->GetPosition();
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
		//CVector4 RevarceRot = { 1.0f - m_StartRot.x,1.0f - m_StartRot.y,1.0f - m_StartRot.z,1.0f };
		//m_StartRot.y*-1.0f;
		//CQuaternion ReverceRot ;
		//ReverceRot.SetRotation(CVector3::AxisY(), -m_StartRot.y
		//CVector3 Back = m_StartForward*-1.0f;
		//CQuaternion BackRot = CQuaternion::Identity();
		//BackRot.SetRotation(Back);
		//CMatrix mBack=CMatrix::Identity();
		//mBack.Inverse(mForward);
		//m_StartRot.SetRotation(mBack);
		//Rot.Multiply(m_StartRot);
		//Rot.Multiply(moveSpeed); 
		m_StartRot.Multiply(moveSpeed);
		Rot.Multiply(moveSpeed);
		//moveSpeed = { moveSpeed.x * Back.x,moveSpeed.y* Back.y,moveSpeed.z*Back.z };
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
	}
	else {
		m_Pos = { 0.0f,200.0f,500.0f };
		g_camera3D.SetTarget(CVector3::Zero());
	}
	//m_Pos = Target + moveSpeed;
	g_camera3D.SetPosition(m_Pos);
	
	//カメラの更新はGameObjectManagerのExcuteGameでやっている。
	//g_camera3D.Update();

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
