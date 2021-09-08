#include "Player.h"
#include "State/IdleState.h"
#include "State/RunState.h"
#include "State/AttackState.h"
#include "State/RollingState.h"
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
	const CVector3 HpPos = { -905.0f,485.0f,0.0f };
	const CVector3 StaminaPos = { -905.0f,460.0f,0.0f };
	const float StaminaMax = 100.0f;
	const float HpSpriteScale = 0.112f;
	const float SpriteY = 25.0f;
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

	InitHpSprite(MaxHp, m_Hp, false, 500.0f, SpriteY);
	SetHpPosition(HpPos);
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

	m_StaminaSprite = NewGO<SpriteRender>(1);
	m_StaminaSprite->Init(L"Stamina_Top_Green.dds", 425.0f, SpriteY);
	m_StaminaSprite->SetPosition(StaminaPos);
	m_StaminaSprite->SetPivot({ SpriteRender::Right(),0.5f });
	m_StaminaFrame = NewGO<SpriteRender>(0);
	m_StaminaFrame->Init(L"HP_Under_Brack.dds", 425.0f, SpriteY);
	m_StaminaFrame->SetPosition(StaminaPos);
	m_StaminaFrame->SetPivot({ SpriteRender::Right(),0.5f });

	ChangeState(m_NextState);

	m_myLuminous = NewGO<PointLight>(0);
	CVector3 LightPos = m_ModelPos;
	LightPos.y += m_Hight * UpPointLight;
	LightPos -= m_forward * disLight;
	m_myLuminous->SetPosition(LightPos);
	m_myLuminous->SetColor(CVector4::White()*2.0f);
	m_myLuminous->SetRenge({ 1200.0f,2.5f,0.0f,0.0f });

	m_RollingSound.Init(L"Rolling.wav");
	m_RollingSound.SetVolume(3.0f);
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
			m_Stamina -= StaminaCostList::StaminaAttack;
			m_PlAttack = NewGO<PlayerAttack>(0, "playerAttack");
			const float AttackDamage = 20.0f;
			const float AttackEria = 95.0f;
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
			if (m_PlAttack == nullptr) {
				m_Stamina -= StaminaCostList::StaminaAttack;
				m_PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
				const float AttackDamage = 30.0f;
				const float AttackEria = 95.0f;
				m_PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
			}
		}
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd2") == 0) {
		DeleteGO(m_PlAttack);
		m_PlAttack = nullptr;
	}
	if (wcscmp(eventName, L"AttackJubgmentStart3") == 0) {
		if (m_PlAttack == nullptr) {
			m_Stamina -= StaminaCostList::StaminaAttack;
			m_PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
			const float AttackDamage = 50.0f;
			const float AttackEria = 95.0f;
			m_PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
			m_IsLastAttack = true;
		}
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd3") == 0) {
		DeleteGO(m_PlAttack);
		m_PlAttack = nullptr;
		m_IsLastAttack = false;
	}
	if (wcscmp(eventName, L"RollAttackStart") == 0) {
		if (m_PlAttack == nullptr) {
			m_PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
			const float AttackDamage = 50.0f;
			const float AttackEria = 105.0f;
			m_PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
		}
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
	if (wcscmp(eventName, L"RollingSound") == 0) {
		m_RollingSound.Play();
	}
}

void Player::AnimetionInit()
{
	LoadAnimation(m_AnimeClip[State::Title], L"siting.tka");
	m_AnimeClip[State::Title].SetLoopFlag(true);

	LoadAnimation(m_AnimeClip[State::Stand], L"Standing.tka");

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
	WeaponRot.SetRotation(CVector3::AxisZ(), BoneDiff);
	CQuaternion mulRot = m_ModelRot;
	mulRot.Multiply(WeaponRot);
	m_weapon->SetRotation(weaponBindRot);
	m_weapon->Update();
	if (m_state == State::Attack) {
		if (!m_ComboAttack&&g_pad[0].IsTrigger(enButtonX)&&!m_IsLastAttack) {
			if (m_Stamina > StaminaCostList::StaminaAttack) {
				m_ComboAttack = true;

			}
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
	CVector3 moveSpeedTarget = m_Animation.Update(gameTime().GetFrameDeltaTime() * m_mulAnimSpeed);

	//3dsMaxの空間からゲーム空間に移動速度を変更。
	float tmp = moveSpeedTarget.y;
	moveSpeedTarget.y = moveSpeedTarget.z;
	moveSpeedTarget.z = -tmp;
	moveSpeedTarget.y = 0.0f;
	moveSpeedTarget.x = 0.0f;

	//モデル空間からワールド空間に変換。
	m_ModelRot.Multiply(moveSpeedTarget);
	
	m_MoveSpeed.Lerp(0.5f, m_MoveSpeed, moveSpeedTarget);

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
	static	CVector3 SpriteScale = CVector3::One();
	SpriteScale.x = m_Stamina / StaminaMax;
	CVector3 AjectStaminaPos = StaminaPos;
	AjectStaminaPos.x+=5.5f*(1.0f - SpriteScale.x);
	m_StaminaSprite->SetPosition(AjectStaminaPos);
	m_StaminaSprite->SetScale(SpriteScale);
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
	SetHpPosition(HpPos);

	if (m_Stamina <= 0.0f&&m_RestStopTime > 2.0f) {
		m_Stamina = 0.0f;
		m_RestStopTime = 0.0f;
	}
	m_RestStopTime += gameTime().GetFrameDeltaTime();
	if (m_Stamina < StaminaMax&&
		m_StaminaRest&&
		m_RestStopTime>2.0f) {
		m_Stamina += 1.0f;
	}
	m_StaminaRest = true;
	if (m_NextState == State::GameClear) {
		m_NewClearTime += gameTime().GetFrameDeltaTime();
	}
	if (m_NewClearTime > 1.5f) {
		if (m_HuntedSprite == nullptr) {
			m_HuntedSprite = NewGO<HuntedSprite>(0);
		}
	}
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
		delete m_currentState;
	}
	DeleteGO(m_myLuminous);
	Destroy();
	DeleteGO(m_StaminaFrame);
	DeleteGO(m_StaminaSprite);
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

	if (m_Stamina > StaminaCostList::StaminaRolling&&g_pad[0].IsPress(enButtonB)) {
		//Aボタンが押されたらバックステップを行う。
		return true;
	}
	return false;

}

bool Player::IsRollingAttack() {
	if (m_Hp < 0.001f) {
		return false;
	}
	if (  g_pad[0].IsPress(enButtonY)&&m_Stamina > StaminaCostList::StaminaRollingAttack) {
		return true;
	}
	return false;
}

bool Player::IsAttack() {
	if (m_Hp < 0.001f) {
		return false;
	}
	if (g_pad[0].IsPress(enButtonX) && m_Stamina > StaminaCostList::StaminaAttack) {
		return true;
	}
	return false;
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
		m_HpTopSprite->SetActiveFlag(false);
		m_HpUnderSprite->SetActiveFlag(false);
		m_HpTopTranslucentSprite->SetActiveFlag(false);
		m_StaminaSprite->SetActiveFlag(false);
		m_StaminaFrame->SetActiveFlag(false);
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
		m_Model->SetAmbientColor(0.6f);
		break;
	case State::Walk:		//走り中
		delete m_currentState;
		m_currentState = new RunState(this);
		break;
	case State::Roling:	//バックステップ中。
		delete m_currentState;
		m_currentState = new RollingState(this);
		m_Stamina -= StaminaCostList::StaminaRolling;
		break;
	case State::Attack:
		delete m_currentState;
		m_currentState = new AttackState(this);
		break;
	case State::RollingAttack:
		delete m_currentState;
		m_currentState = new RollingAttackState(this);
		m_Stamina -= StaminaCostList::StaminaRollingAttack;
		break;
	case State::Damage:
		if (m_PlAttack != nullptr) {
			DeleteGO(m_PlAttack);
			m_PlAttack = nullptr;
			m_IsLastAttack = false;
		}
		delete m_currentState;
		m_currentState = new DamageState(this);
		break;
	case State::Die:
		delete m_currentState;
		m_currentState = new DieState(this);
		break;
	case State::GameClear:
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