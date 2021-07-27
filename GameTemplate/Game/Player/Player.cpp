#include "Player.h"
#include "State/IdleState.h"
#include "State/RunState.h"
#include "State/AttackState.h"
#include "State/BackStepState.h"
#include "State/RollingAttackState.h"
#include "State/DamageState.h"
#include "Player.h"
#include "State/DieState.h"
#include "HuntedSprite.h"
#include "PlayerAttack.h"
#include "weapon/IWeapon.h"
#include "weapon/Sword.h"
#include "State/TitleState.h"
#include "State/StandingState.h"

namespace {
	const float radius = 35.0f;//キャラコンの横幅
	const float MaxHp = 62.5f;
	const float AttackReach = 100.0f;
	const float disLight = 0.0f;//プレイヤーからどれだけ離すか
	const float UpPointLight = 0.8f;
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
	CharacterInit(L"Player.cmo", radius, m_height, m_ModelPos);

	AnimetionInit();

	const float InterpolateTime = 0.2f;
	m_Animation.Play(m_NextState, InterpolateTime);
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {

		OnAnimEvent(eventName);
	});

	InitHpSprite(MaxHp,m_Hp, HpScale::PlayerHP);

#ifdef _DEBUG
	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"DebugShere.cmo");
	//zはワールド空間でのｙにあたる
	//yは考慮しない
	m_HitModel->SetScale({ radius, radius, 1.0f });
#endif
	m_WalkSound.Init(L"Walk.wav");
	m_WalkSound2.Init(L"Walk.wav");
	m_SwingSound.Init(L"SwingSword.wav");

	m_weapon = new Sword();
	m_weapon->SetPosition(m_ModelPos); 
	m_weapon->Start();
	m_weapon->GetModel()->SetAmbientColor(0.4f);

	m_Model->SetAmbientColor(0.0f);

	ChangeState(m_NextState);

	m_myLuminous = NewGO<PointLight>(0);
	CVector3 LightPos = m_ModelPos;
	LightPos.y += m_Hight * UpPointLight;
	LightPos -= m_forward * disLight;
	m_myLuminous->SetPosition(LightPos);
	m_myLuminous->SetColor(CVector4::White()*2.0f);
	m_myLuminous->SetRenge({ 1200.0f,2.5f,0.0f,0.0f });	
	m_Model->SetShadowRecive(false);
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
		m_SwingSound.Play();
		if (m_PlAttack == nullptr) {
			m_PlAttack = NewGO<PlayerAttack>(0, "playerAttack");
			const float AttackDamage = 20.0f;
			const float AttackEria = 75.0f;
			m_AttackPos = m_ModelPos + m_forward * AttackReach;
			m_PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
		}
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd1") == 0) {
		DeleteGO(m_PlAttack);
		m_PlAttack = nullptr;
	}
	if (wcscmp(eventName, L"AttackJubgmentStart2") == 0) {
		if (m_ComboAttack) {
			m_ComboAttack = false;
			if (m_PlAttack = nullptr) {
				m_PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
				const float AttackDamage = 30.0f;
				const float AttackEria = 75.0f;
				m_PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
			}
		}
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd2") == 0) {
		DeleteGO(m_PlAttack);
		m_PlAttack = nullptr;
	}
	if (wcscmp(eventName, L"AttackJubgmentStart3") == 0) {
		m_PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
		const float AttackDamage = 100.0f;
		const float AttackEria = 95.0f;
		m_PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd3") == 0) {
		DeleteGO(m_PlAttack);
		m_PlAttack = nullptr;
	}
	if (wcscmp(eventName, L"RollAttackStart") == 0) {
		m_PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
		const float AttackDamage = 80.0f;
		const float AttackEria = 105.0f;
		m_PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"RollAttackEnd") == 0) {
		DeleteGO(m_PlAttack);
		m_PlAttack = nullptr;
	}
	if (wcscmp(eventName, L"WalkSound") == 0) {
		m_WalkSound.Play();
	}
	if (wcscmp(eventName, L"WalkSound2") == 0) {
		m_WalkSound2.Play();
	}
}

void Player::AnimetionInit()
{
	LoadAnimation(m_AnimeClip[State::Title], L"siting.tka");
	m_AnimeClip[State::Title].SetLoopFlag(true);

	LoadAnimation(m_AnimeClip[State::Stand],L"Standing.tka");
	
	LoadAnimation(m_AnimeClip[State::TakeOut], L"WeaponTakeOut.tka");

	LoadAnimation(m_AnimeClip[State::TitleWalk], L"Idle.tka");
	m_AnimeClip[State::Walk].SetLoopFlag(true);

	LoadAnimation(m_AnimeClip[State::Idle], L"Idle.tka");
	m_AnimeClip[State::Idle].SetLoopFlag(true);

	LoadAnimation(m_AnimeClip[State::Walk], L"walk.tka");
	m_AnimeClip[State::Walk].SetLoopFlag(true);

	LoadAnimation(m_AnimeClip[State::Roling], L"Rolling.tka");

	LoadAnimation(m_AnimeClip[State::Attack], L"Attack.tka");
	m_AnimeClip[Attack].SetLoopFlag(false);

	LoadAnimation(m_AnimeClip[State::RollingAttack], L"RollingAttack.tka");

	LoadAnimation(m_AnimeClip[State::Damage], L"damage.tka");

	LoadAnimation(m_AnimeClip[State::Die], L"Die.tka");

	LoadAnimation(m_AnimeClip[State::GameClear], L"VictoryPose.tka");

	InitAnimation(m_AnimeClip, State::Num);

}

void Player::Update()
{
	CVector3 weaponPos = m_Model->GetModel().FindBone(L"PlayerWeapon")->GetPosition();
	m_weapon->SetPosition(weaponPos);
	CVector3 weaponBindPos = m_Model->GetModel().FindBone(L"PlayerWeaponBind")->GetPosition();
	CQuaternion weaponBindRot = m_Model->GetModel().FindBone(L"PlayerWeapon")->GetRotation();
	CVector3 BoneDiff = weaponBindPos - weaponPos;
	BoneDiff.Normalize();
	CQuaternion WeaponRot = CQuaternion::Identity();
	//CMatrix mRot = CMatrix::Identity();
	//mRot.MakeRotationFromQuaternion(m_ModelRot);
	//m_Left = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	//m_Left.Normalize();
	//float WeaponRotAngle = BoneDiff.Dot(m_Left);
	WeaponRot.SetRotation(CVector3::AxisZ(), BoneDiff);
	CQuaternion mulRot = m_ModelRot;
	mulRot.Multiply(WeaponRot);
	m_weapon->SetRotation(weaponBindRot);
	m_weapon->Update();
	if (m_state == State::Attack) {
		if (g_pad[0].IsTrigger(enButtonX)) {
			m_ComboAttack = true;
		}
	}
	CVector3 LightPos = m_ModelPos;
	LightPos.y += 500.0f;
	LightPos.z += 250.0f;
	LightPos.x -= 500.0f;
	g_graphicsEngine->GetShadowMap()->SetLightCameraPosition(LightPos);
	g_graphicsEngine->GetShadowMap()->SetLightCameraTarget(m_ModelPos);

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

#ifdef _DEBUG
	//当たり判定を更新
	m_HitModel->SetPosition(m_ModelPos);
#endif
	if (m_PlAttack != nullptr) {
		if (m_PlAttack->IsHit()) {
			Heal();
		}
	}

	CVector3 PointLightPos = m_ModelPos;
	PointLightPos.y += m_Hight * UpPointLight;
	PointLightPos -= m_forward * disLight;
	m_myLuminous->SetPosition(PointLightPos);
}
void Player::OnDestroy()
{
#ifdef _DEBUG
	DeleteGO(m_HitModel);
#endif
	if (m_HuntedSprite != nullptr) {
		DeleteGO(m_HuntedSprite);
		m_HuntedSprite = nullptr;
	}
	m_weapon->Delete();
	delete m_weapon;
	if (m_currentState != nullptr) {
		m_currentState->Delete();
		delete m_currentState;
	}
	DeleteGO(m_myLuminous);
	Destroy();
}
void Player::Rotate()
{
	if (m_currentState->IsPossibleRotate()) {
		//カメラの方向に合わせて向かせる
		CVector3 MoveSpeed = g_camera3D.GetForward()*g_pad[0].GetLStickYF();
		CVector3 MoveScale = MoveSpeed + (g_camera3D.GetRight()* g_pad[0].GetLStickXF());
		if (MoveScale.Length() < 0.01f) {
			return;
		}
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
	if (m_state == State::GameClear) {
		return 0.0f;
	}
	//左スティックの入力があればtrueを返す。
	return fabsf(g_pad[0].GetLStickXF()) > 0.0f || fabsf(g_pad[0].GetLStickYF());
}
bool Player::IsBackStep() const
{
	if (m_Hp < 0.001f) {
		return false;
	}
	//Aボタンが押されたらバックステップを行う。
	return g_pad[0].IsPress(enButtonA);

}

bool Player::IsRollingAttack() {
	if (m_Hp < 0.001f) {
		return false;
	}
	return  g_pad[0].IsPress(enButtonY);
}

bool Player::IsAttack() {
	if (m_Hp < 0.001f) {
		return false;
	}
	return g_pad[0].IsPress(enButtonX);
}
void Player::ChangeState(int state)
{
	//引数で渡されたステートのインスタンスを作成。
	switch (state) {
	case State::Title:
		if (m_currentState != nullptr) {
			delete m_currentState;
		}
		m_currentState = new TitleState(this);
		m_HpTopSprite->SetAlpha(0.0f);
		m_HpUnderSprite->SetAlpha(0.0f);
		m_HpTopTranslucentSprite->SetAlpha(0.0f);
		m_Model->SetAmbientColor(0.0f);
		break;
	case State::Stand:
		delete m_currentState;
		m_currentState = new StandingState(this);
		break;
	case State::Idle:
		if (m_currentState != nullptr) {
			delete m_currentState;
		}
		m_currentState = new IdleState(this);
		m_HpTopSprite->SetAlpha(1.0f);
		m_HpUnderSprite->SetAlpha(1.0f);
		m_Model->SetAmbientColor(1.0f);
		break;
	case State::Walk:		//走り中
		delete m_currentState;
		m_currentState = new RunState(this);
		break;
	case State::Roling:	//バックステップ中。
		delete m_currentState;
		m_currentState = new BackStepState(this);
		break;
	case State::Attack:
		delete m_currentState;
		m_currentState = new AttackState(this);
		break;
	case State::RollingAttack:
		delete m_currentState;
		m_currentState = new RollingAttackState(this);
		break;
	case State::Damage:
		if (m_PlAttack != nullptr) {
			DeleteGO(m_PlAttack);
			m_PlAttack = nullptr;
		}
		delete m_currentState;
		m_currentState = new DamageState(this);
		break;
	case State::Die:
		delete m_currentState;
		m_currentState = new DieState(this);
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