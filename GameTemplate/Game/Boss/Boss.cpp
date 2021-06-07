#include "Boss.h"
#include "Player/Player.h"
#include "State/BossAppearanceRoarState.h"
#include "State/BossAttackState.h"
#include "State/BossDieState.h"
#include "State/BossWalkState.h"
#include "State/BossNormalRoar.h"
#include "State/IBossState.h"
#include "GameSceneFunction/Attack.h"

namespace {
	const float radius = 60.0f;		//キャラコンの幅
	const float height = 130.0;		//キャラコンの高さ
	const float modelScale = 1.8f;	//モデルの大きさ
	const float InPlayer = 200.0f;	//プレイヤーが攻撃範囲内にいるかどうかに使う
	const float Damage = 15.0f;		//ダメージ
	const float Eria = 70.0f;		//攻撃範囲
	const float BossMaxHp = 300.0f;	//ボス最大のHP
	const float HpSpriteSizeX = 1.5625f;

	const float hpSpriteSizeY = 10.0f;	//スプライトの縦幅
	//const float HpSpriteSizeX = 1.5625f;
	//スプライトの基点をずらしているので
	//そのズレを修正
	const float spriteFix = -50.0f;
	float Hight = 0.0f;
	//HPをちょっと上に置く
	const float HpPosUp = 30.0f;
	const float HpSpriteDead = 0.0f;//ボスが死んだときにHpバーを見えなくする
}

bool Boss::Start() {
	m_ModelPos = m_SpownPosition;
	CharacterInit(L"Boss.cmo", radius, height, m_ModelPos);
	AnimationInit();
	m_player = FindGO<Player>("player");
	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"DebugShere.cmo");
	//zはワールド空間でのｙにあたる
	//yは考慮しない
	m_HitModel->SetScale({ radius, radius, 1.0f });
	AttackReach = 150.0f;

	InitHpSprite(BossMaxHp, HpScale::BossHP);
	InitSprite();
	m_RoarSound.Init(L"RoarSound.wav");
	m_HpTopSprite->SetAlpha(0.0f);
	m_HpUnderSprite->SetAlpha(0.0f);
	return true;
}

void Boss::Update()
{
	//状態を変更
	ChengeState(m_NextState);
	//現在の状態を更新
	m_ActiveState->Update();
	//Animationをプレイ
	m_Animation.Play(m_CurrentState);
	//咆哮を更新
	RoarUpdate();
	//Boss用のスプライトにHpを設定
	m_BossSprite->SetHp(m_Hp);
	//CharactorクラスのHpバーの更新
	SpriteUpdate();
	//前方向を更新
	ForwardUpdate();
}

void Boss::OnDestroy()
{
	DeleteGO(m_HitModel);
	DeleteGO(m_BossSprite);
}

void Boss::IsChengeAttackState()
{
	CVector3 Diff = m_player->GetPosition() - m_ModelPos;
	if (Diff.Length() < InPlayer) {
		m_NextState = State::Attack;
	}
}

void Boss::IsChengeNormalRoar()
{
	m_RoarTime += gameTime().GetFrameDeltaTime();
	if (m_RoarTime > m_CoolTimeRoar) {
		m_RoarTime = 0;
		m_NextState = State::NormalRoar;
	}
}

void Boss::ChengeState(const State& state)
{
	switch (state) {
	case State::Walk:
		m_ActiveState = new BossWalkState(this);
		m_CurrentState = state;
		break;
	case State::Attack:
		m_ActiveState = new BossAttackState(this);
		m_CurrentState = state;
		break;
	case State::AppearanceRoar:
		m_ActiveState = new BossAppearanceRoarState(this);
		m_CurrentState = state;
		DeleteGO(m_HaveAttack);
		m_HaveAttack = nullptr;
		break;
	case State::NormalRoar:
		m_ActiveState = new BossNormalRoar(this);
		DeleteGO(m_HaveAttack);
		m_HaveAttack = nullptr;
		m_CurrentState = state;
		break;
	case State::Die:
		m_ActiveState = new BossDieState(this);
		m_HpUnderSprite->SetAlpha(HpSpriteDead);
		m_CurrentState = state;
	default:
		break;
	}
}

void Boss::Rotate()
{
	//プレイヤーとの距離を測る
	CVector3 diff = m_player->GetPosition() - m_ModelPos;
	//距離の方向を使って回転量を求める
	float angle = atan2(diff.x, diff.z);
	//回転量を保存
	m_ModelRot.SetRotation(CVector3::AxisY(), angle);
	//前方向を更新
	ForwardUpdate();
}

void Boss::AnimationInit()
{
	//アニメーションデータを読みこむ
	LoadAnimation(m_AnimationClip[State::Walk], L"BossWalk.tka");
	m_AnimationClip[State::Walk].SetLoopFlag(true);
	LoadAnimation(m_AnimationClip[State::Attack], L"BossAttack.tka");
	LoadAnimation(m_AnimationClip[State::AppearanceRoar], L"BossAppearanceRoar.tka");
	LoadAnimation(m_AnimationClip[State::NormalRoar], L"BossNormalRoar.tka");
	LoadAnimation(m_AnimationClip[State::Down], L"BossDown.tka");
	LoadAnimation(m_AnimationClip[State::Die], L"BossDie.tka");

	//アニメーションを初期化
	InitAnimation(m_AnimationClip,State::StateNum);
	//イベントリスナーを設定
	m_Animation.AddAnimationEventListener([&](const wchar_t* ClipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}

void Boss::OnAnimEvent(const wchar_t * eventName)
{	
	//AttackStartの名前を見つけたら
	if (wcscmp(eventName, L"AttackStart") == 0) {
		//攻撃判定を作る
		AIAttack(Damage, Eria);
	}
	//AttackEndの名前を見つけたら
	if (wcscmp(eventName, L"AttackEnd") == 0) {
		//攻撃判定を消す
		DeleteGO(m_HaveAttack);
		m_HaveAttack = nullptr;
	}
	if (wcscmp(eventName, L"RoorSound") == 0) {
		m_RoarSound.Play();
	}
}

void Boss::RoarUpdate()
{
	m_RoarTime += gameTime().GetFrameDeltaTime();
}

void Boss::InitSprite()
{
	m_BossSprite = NewGO< BossHpSprite>(0);
	m_BossSprite->SetHp(m_MaxHp);
}
