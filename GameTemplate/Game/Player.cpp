#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	return true;
}

void Player::Update()
{
	if (g_pad[0].IsPress(enButtonRight)) {
		m_pos.x -= 1.0f;
	}
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_pos.x += 1.0f;
	}

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}