#include "pch.h"
#include "GameCamera.h"
#include "Player/Player.h"

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

	m_springCamera.Init(g_camera3D, 1000.0f);
	m_springCamera.Refresh();
	return true;
}

void GameCamera::Update()
{
	//����I�ɃJ���������t���b�V������
	if (m_refleshTimer > 0.0f) {
		m_refleshTimer -= gameTime().GetFrameDeltaTime();
		if (m_refleshTimer > 0.0f) {
			m_springCamera.Refresh();
		}
	}
	if (m_player != nullptr) {
		CVector3 PlayerPos = m_player->GetPosition();
		CVector3 Target = { PlayerPos.x,PlayerPos.y + m_player->GetHeight(),PlayerPos.z };
		m_springCamera.SetTarget(Target);
		CVector3 moveSpeed = CVector3::Zero();
		moveSpeed = PlayerCameraLeave;
		CQuaternion Rot = CQuaternion::Identity();
		//�p�b�h���͂̍ŏ�
		const float NotEntered = 0.001f;
		//�p�b�h�̓��͂�����Ă����
		if (fabsf(g_pad[0].GetRStickXF()) > NotEntered) {
			//���E�̉�]�ʂ𒲐�
			const float XRotVolum = 2.0f;
			m_AngleX += g_pad[0].GetRStickXF()*XRotVolum;
		}
		Rot.SetRotationDeg(CVector3::AxisY(), -m_AngleX);
		m_StartRot.Multiply(moveSpeed);
		Rot.Multiply(moveSpeed);
		//�v���C���[���炿����ƃJ�����̏I�_�ɋ߂��ꏊ
		CVector3 RayStart = Target + moveSpeed * 0.01f;

		m_CharaCon.SetPosition(RayStart);
		//�����̉�]�ʂ𒲐�
		const float YRotVolum = 20.0f;
		m_AngleY += g_pad[0].GetRStickYF()*YRotVolum;
		//�����̏��
		const float UpperLimit = 300.0f;
		//�����̉���
		const float LowerLimmit = -50.0f;
		if (m_AngleY < LowerLimmit) {
			m_AngleY = LowerLimmit;
		}
		if (m_AngleY > UpperLimit) {
			m_AngleY = UpperLimit;
		}
		moveSpeed.y += m_AngleY;
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
		m_springCamera.SetTarget(CVector3::Zero());
	}
	
	//m_Pos = Target + moveSpeed;
	m_springCamera.SetPosition(m_Pos);
	
	m_springCamera.Update();
	//�J�����̍X�V��GameObjectManager��ExcuteGame�ł���Ă���B
	//g_camera3D.Update();
}
