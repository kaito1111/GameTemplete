#include "Player.h"
#include "State/PlayerStateIdle.h"
#include "State/PlayerStateRun.h"
#include "State/PlayerStateAttack.h"
#include "State/PlayerStateBackStep.h"
#include "State/PlayerStateRollingAttack.h"
#include "State/PlayerStateDamage.h"
#include "Player.h"
#include "State/PlayerDieState.h"
#include "State/PlayerStateGameClear.h"
#include "HuntedSprite.h"
#include "PlayerAttack.h"

namespace {
	const float radius = 35.0f;//キャラコンの横幅
	const float MaxHp = 62.5f;
	const float AttackReach = 100.0f;
}
Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	m_ModelScale = { 0.8f,0.8f,0.8f };  //プレイヤーの大きさ
								    	//設定上少し小さくする
	m_ModelPos = m_SpownPosition;
	CharacterInit(L"Player.cmo", radius,m_height,m_ModelPos);
	//待機ステートを作成する。
	m_currentState = new PlayerStateIdle(this);

	AnimetionInit();

	const float InterpolateTime = 0.2f;
	m_Animation.Play(State::Idle, InterpolateTime);
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {

		OnAnimEvent(eventName);
	});

	InitHpSprite(MaxHp,HpScale::PlayerHP);

	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"DebugShere.cmo");
	//zはワールド空間でのｙにあたる
	//yは考慮しない
	m_HitModel->SetScale({ radius, radius, 1.0f });
	return true;
}
void Player::OnAnimEvent(const wchar_t* eventName)
{
	if (wcscmp(eventName, L"AttackEnd1") == 0) {
		if (!m_ComboAttack) {
			SetIdleState();
		}
	}
	if (wcscmp(eventName, L"AttackEnd2") == 0) {
		if (!m_ComboAttack) {
			SetIdleState();
		}
		m_ComboAttack = false;
	}
	if (wcscmp(eventName, L"AttackJubgmentStart1") == 0) {
		PlayerAttack* PlAttack = NewGO<PlayerAttack>(0, "playerAttack");
		const float AttackDamage = 20.0f;
		const float AttackEria = 75.0f;
		m_AttackPos = m_ModelPos + m_forward * AttackReach;
		PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd1") == 0) {
		DeleteGO("playerAttack");
	}
	if (wcscmp(eventName, L"AttackJubgmentStart2") == 0) {
		if (m_ComboAttack) {
			m_ComboAttack = false;
			PlayerAttack* PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
			const float AttackDamage = 30.0f;
			const float AttackEria = 75.0f;
			PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
		}
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd2") == 0) {
		DeleteGO("playerAttack");
	}
	if (wcscmp(eventName, L"AttackJubgmentStart3") == 0) {
		PlayerAttack* PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
		const float AttackDamage = 100.0f;
		const float AttackEria = 95.0f;
		PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd3") == 0) {
		DeleteGO("playerAttack");
	}
	if (wcscmp(eventName, L"RollAttackStart") == 0) {
		PlayerAttack* PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
		const float AttackDamage = 80.0f;
		const float AttackEria = 105.0f;
		PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"RollAttackEnd") == 0) {
		DeleteGO("playerAttack");
	}
}

void Player::AnimetionInit()
{
	LoadAnimation(m_AnimeClip[State::Idle],L"idol.tka"); 
	m_AnimeClip[State::Idle].SetLoopFlag(true);

	LoadAnimation(m_AnimeClip[State::Walk],L"walk.tka");
	m_AnimeClip[State::Walk].SetLoopFlag(true);

	LoadAnimation(m_AnimeClip[State::Roling], L"Rolling.tka");

	LoadAnimation(m_AnimeClip[State::Attack],L"Attack.tka");
	m_AnimeClip[Attack].SetLoopFlag(false);

	LoadAnimation(m_AnimeClip[State::RollingAttack],L"RollingAttack.tka");

	LoadAnimation(m_AnimeClip[State::Damage],L"damage.tka");

	LoadAnimation(m_AnimeClip[State::Die], L"Die.tka");

	LoadAnimation(m_AnimeClip[State::GameClear],L"VictoryPose.tka");

	InitAnimation(m_AnimeClip, State::Num);

}

void Player::Update()
{
	if (m_state == State::Attack) {
		if (g_pad[0].IsTrigger(enButtonX)) {
			m_ComboAttack = true;
		}
	}

	//状態を切り替え
	ChangeState(m_NextState);
	//状態の更新
	UpdateState();

	//HPスプライトの更新
	SpriteUpdate();

	//キャラコン上での移動
	m_MoveSpeed = m_Animation.Update(gameTime().GetFrameDeltaTime() * m_mulAnimSpeed);

	//3dsMaxの空間からゲーム空間に移動速度を変更。
	float tmp = m_MoveSpeed.y;
	m_MoveSpeed.y = m_MoveSpeed.z;
	m_MoveSpeed.z = -tmp;

	//モデル空間からワールド空間に変換。
	m_ModelRot.Multiply(m_MoveSpeed);

	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Model->GetModel());

	//移動処理
	PlayerMove();

	//回転処理
	Rotate();

	//モデルの更新
	CharacterModelUpdate();

	//前方向の更新
	ForwardUpdate();

	//攻撃発生位置を更新
	const float AttackReach = 100.0f;
	m_AttackPos = m_ModelPos + m_forward * AttackReach;

	//当たり判定を更新
	m_HitModel->SetPosition(m_ModelPos);
}
void Player::OnDestroy()
{
	DeleteGO(m_HitModel);
	if (m_HuntedSprite != nullptr) {
		DeleteGO(m_HuntedSprite);
		m_HuntedSprite = nullptr;
	}
}
void Player::Rotate()
{
	if (m_currentState->IsPossibleRotate()) {
		//カメラの方向に合わせて向かせる
		CVector3 MoveSpeed = g_camera3D.GetForward()*g_pad[0].GetLStickYF();
		MoveSpeed -= g_camera3D.GetRight()*g_pad[0].GetLStickXF();
		//走り状態時。
		m_ModelRot.SetRotation(CVector3::AxisY(), atan2(MoveSpeed.x, MoveSpeed.z));
	}
}
void Player::PlayerMove()
{
	if (m_currentState->IsPossibleMove()) {
		//プレイヤーの移動量はアニメーションの再生から引っ張ってくる。
		if (m_MoveSpeed.Length() < 1.0f) {
			m_MoveSpeed = CVector3::Zero();
		}
		Move(m_MoveSpeed);
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
	return  g_pad[0].IsPress(enButtonY);
}

bool Player::IsAttack() {
	return g_pad[0].IsPress(enButtonX);
}
void Player::ChangeState(int state)
{
	//引数で渡されたステートのインスタンスを作成。
	switch (state) {
	case State::Idle:
		if (m_currentState != nullptr) {
			delete m_currentState;
		}
		m_currentState = new PlayerStateIdle(this);
		break;
	case State::Walk:		//走り中
		delete m_currentState;
		m_currentState = new PlayerStateRun(this);
		break;
	case State::Roling:	//バックステップ中。
		delete m_currentState;
		m_currentState = new PlayerStateBackStep(this);
		
		break;
	case State::Attack:
		delete m_currentState;
		m_currentState = new PlayerStateAttack(this);
		break;
	case State::RollingAttack:
		delete m_currentState;
		m_currentState = new PlayerStateRollingAttack(this);
		break;
	case State::Damage:
		DeleteGOs("playerAttack");
		delete m_currentState;
		m_currentState = new PlayerStateDamage(this);
		break;
	case State::Die:
		delete m_currentState;
		m_currentState = new PlayerDieState(this);
		break;
	case State::GameClear:
		if (m_HuntedSprite == nullptr) {
			m_HuntedSprite = NewGO<HuntedSprite>(0);
		}
		break;
	default:
		break;
	}

	m_state = state;
}

void Player::UpdateState()
{
	m_currentState->Update();
	if (m_state != m_NextState) {
		ChangeState(m_NextState);
	}
}