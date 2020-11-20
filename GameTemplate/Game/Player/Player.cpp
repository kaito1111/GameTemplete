#include "Player.h"
#include "State/PlayerStateIdle.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	m_Model = NewGO<SkinModelRender>(0);
	//cmoファイルの読み込み。
	m_Model->Init(L"Assets/modelData/PlayerArmor.cmo");
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	//m_CharaCon.Init(20.0f, 80.0f, m_Pos);

	//待機ステートを作成する。
	m_currentState = new PlayerStateIdle(this);

	m_AnimeClip[AnimePattern::idol].Load(L"Assets/animData/idol.tka");
	m_AnimeClip[AnimePattern::idol].SetLoopFlag(true);

	m_AnimeClip[AnimePattern::walk].Load(L"Assets/animData/walk.tka");
	m_AnimeClip[AnimePattern::walk].SetLoopFlag(true);
	
	m_AnimeClip[Back].Load(L"Assets/animData/back.tka");

	m_AnimeClip[AnimePattern::Attack].Load(L"Assets/animData/Attack.tka");

	m_AnimeClip[AnimePattern::RollingAttack].Load(L"Assets/animData/RollingAttack.tka");

	m_Animation.Init(m_Model->GetModel(), m_AnimeClip, AnimePattern::AnimeNum);

//	m_Model->SetRenderMode(RenderMode::Silhouette);
	return true;
}

void Player::Update()
{
	UpdateState();
	m_MoveSpeed = m_Animation.Update(1.0f / 60.0f * m_mulAnimSpeed);
	//3dsMaxの空間からゲーム空間に移動速度を変更。
	float tmp = m_MoveSpeed.y;
	m_MoveSpeed.y = m_MoveSpeed.z;
	m_MoveSpeed.z = -tmp;
	//モデル空間からワールド空間に変換。
	m_Rot.Multiply(m_MoveSpeed);
	
	PlayerMove();
	PlayerRotate();
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
}
void Player::PlayerRotate()
{
	if (m_currentState->IsPossibleRotate()) {
		//走り状態のときのみ。
		m_Rot.SetRotation(CVector3::AxisY(), atan2(-g_pad[0].GetLStickXF(), -g_pad[0].GetLStickYF()));
	}
}
void Player::PlayerMove()
{
	if (m_currentState->IsPossibleMove()) {
		//プレイヤーの移動量はアニメーションの再生から引っ張ってくる。
		m_Pos += m_MoveSpeed;
	}
}
bool Player::IsMove() const
{
	//左スティックの入力があればtrueを返す。
	return fabsf(g_pad[0].GetLStickXF()) > 0.0f || fabsf(g_pad[0].GetLStickYF());
}
bool Player::IsBackStep() const
{
	//Aボタンが押されたらバックステップを行う。
	return g_pad[0].IsPress(enButtonA);

}

bool Player::IsRollingAttack() {
	return g_pad[0].IsPress(enButtonY);
}

bool Player::IsAttack() {
	return g_pad[0].IsPress(enButtonX);
}
void Player::ChangeState(State state)
{
	//引数で渡されたステートのインスタンスを作成。
	switch (state) {
	case State_Idle:
		m_currentState = new PlayerStateIdle(this);
		break;
	case State_Run:		//走り中

		break;
	case State_Backstep:	//バックステップ中。

		break;
	case State_Attack:

		break;
	case State_RollingAttack:

		break;
	}

	m_state = state;

}
void Player::UpdateState()
{
	m_currentState->Update();
	//各状態ごとの処理
/*	switch (m_state) {
	case State_Idle:
		m_mulAnimSpeed = 1.0f;
		//待機状態の処理
		m_Animation.Play(idol, 0.2f);
		if (IsMove()) {
			m_state = State_Run;
		}
		if (IsBackStep()) {
			m_state = State_Backstep;
		}
		if (IsAttack()) {
			m_state = State_Attack;
		}
		if (IsRollingAttack()) {
			m_state = State_RollingAttack;
		}
		break;
	case State_Run:
		m_mulAnimSpeed = 1.0f;
		m_Animation.Play(walk, 0.2f);
		if (!IsMove()) {
			//コントローラーの入力が終わった。
			m_state = State_Idle;
		}
		if (IsBackStep()) {
			m_state = State_Backstep;
		}
		if (IsAttack()) {
			m_state = State_Attack;
		}
		if (IsRollingAttack()) {
			m_state = State_RollingAttack;
		}
		break;
	case State_Backstep:
		//バックステップ中はアニメーションの再生速度を2倍に。
		m_mulAnimSpeed = 1.5f;
		m_Animation.Play(Back, 0.2f);
		if (m_Animation.IsPlaying() == false) {
			m_state = State_Idle;
		}
		break;
	case State_Attack:
		m_mulAnimSpeed = 1.0f;
		m_Animation.Play(AnimePattern::Attack, 0.2f);
		if (m_Animation.IsPlaying() == false) {
			m_state = State_Idle;
		}
	case State_RollingAttack:
		m_mulAnimSpeed = 1.0f;
		m_Animation.Play(AnimePattern::RollingAttack,0.2f);
		if (m_Animation.IsPlaying() == false) {
			m_state = State_Idle;
		}
	}*/
}


