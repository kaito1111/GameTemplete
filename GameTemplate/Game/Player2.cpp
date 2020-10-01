#include "Player2.h"

Player2::Player2()
{
	//cmoファイルの読み込み。
	m_skin.Init(L"Assets/modelData/unityChan.cmo");
}

Player2::~Player2()
{
}

bool Player2::Start()
{
	return true;
}

void Player2::Update()
{
	if (g_pad[0].IsPress(enButtonUp)) {
		m_pos.y += 1.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_pos.y -= 1.0f;
	}
	//ワールド行列の更新。
	m_skin.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void Player2::Draw()
{
	m_skin.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
