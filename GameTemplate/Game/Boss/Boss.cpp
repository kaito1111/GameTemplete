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
	//スプライトの基点をずらしているので
	//そのズレを修正
	const float spriteFix = -50.0f;
	const float HpPosUp = 30.0f;	//HPをちょっと上に置く
	const float HpSpriteDeadAlpha = 0.0f;//ボスが死んだときにHpバーを見えなくする
	const float ModelAmbientColor = 0.2f;//モデルの環境光の明るさ
	const float EffectScale = 4.0f;
}

bool Boss::Start() {
	//キャラクターコントローラーを初期化し、物理ワールドに登録
	CharacterInit(L"Boss.cmo", radius, height, m_ModelPos);
	//モデルのポジションを設定
	m_Model->SetPosition(m_ModelPos);

	//アニメーションの初期化を呼ぶ
	AnimationInit();

	//モデルの回転の更新を呼ぶ
	Rotate();
	//モデルの回転を設定
	m_Model->SetRotation(m_ModelRot);

	//プレイヤーを見つける
	m_player = FindGO<Player>("player");

#ifdef _DEBUG
	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"DebugShere.cmo");
	//zはワールド空間でのｙにあたる
	//yは考慮しない
	m_HitModel->SetScale({ radius, radius, 1.0f });
#endif
	//攻撃範囲
	AttackReach = 150.0f;

	//HPを最大HPに設定
	m_Hp = BossMaxHp;

	//スプライトの初期化関数を呼ぶ
	InitSprite();

	//咆哮音を設定
	m_RoarSound.Init(L"RoarSound.wav");
	InitHpSprite(m_Hp, m_MaxHp);
	//Hpスプライトの透明度
	//頭の上のHPスプライトはあえて見せないので0にする
	m_HpTopSprite->SetAlpha(0.0f);
	m_HpUnderSprite->SetAlpha(0.0f);
	m_HpTopTranslucentSprite->SetAlpha(0.0f);

	//モデルの環境光を設定する
	m_Model->SetAmbientColor(ModelAmbientColor);
	return true;
}

void Boss::Update()
{
	if (m_NextState != m_CurrentState) {
		//状態を変更
		ChengeState(m_NextState);
	}
	//現在の状態を更新
	m_ActiveState->Update();
	//Animationをプレイ
	m_Animation.Play(m_CurrentState);
	//Boss用のスプライトにHpを設定
	m_BossSprite->SetHp(m_Hp);
	//CharactorクラスのHpバーの更新
	SpriteUpdate();
	//前方向を更新
	ForwardUpdate();
}

void Boss::OnDestroy()
{
#ifdef _DEBUG
	//当たり判定が見えるモデルの削除
	DeleteGO(m_HitModel);
#endif
	//ボスのHp残量を表しているスプライトを削除
	DeleteGO(m_BossSprite);
	//CharactorクラスのDestroy関数を呼ぶ
	Destroy();
	//現在の状態を表しているクラスがnullptrでないなら
	if (m_ActiveState != nullptr) {
		//現在の状態を更新しているクラスを削除
		delete m_ActiveState;
	}
}

void Boss::IsChengeAttackState()
{
	//プレイヤーと距離を測る
	CVector3 Diff = m_player->GetPosition() - m_ModelPos;
	//もしプレイヤーが攻撃エリア内なら
	if (Diff.Length() < InPlayer) {
		//次の状態は攻撃になる
		m_NextState = State::Attack;
	}
}

void Boss::IsChengeNormalRoar()
{
	//咆哮をしていない時間を測る
	m_RoarTime += gameTime().GetFrameDeltaTime();
	//咆哮をしていない時間がクールタイム以上なら
	if (m_RoarTime > m_CoolTimeRoar) {
		//咆哮したので0に戻す
		m_RoarTime = 0;
		//次の状態を普通の咆哮にする
		m_NextState = State::NormalRoar;
	}
}

void Boss::ChengeState(const State& state)
{
	//次の状態によって処理を変える
	switch (state) {
	case State::Walk:
		//現在の状態をWalkに変更
		m_ActiveState = new BossWalkState(this);
		//列挙型の状態も変更
		m_CurrentState = state;
		break;
	case State::Attack:
		//現在の状態をAttackに変更
		m_ActiveState = new BossAttackState(this);
		//列挙型の状態も変更
		m_CurrentState = state;
		break;
	case State::AppearanceRoar:
		//現在の状態を登場時の咆哮状態に変更
		m_ActiveState = new BossAppearanceRoarState(this);
		//列挙型の状態も変更
		m_CurrentState = state;
		break;
	case State::NormalRoar:
		//現在の状態を通常の咆哮状態に変更
		m_ActiveState = new BossNormalRoar(this);
		//攻撃中なら攻撃判定を消す
		DeleteAttack();
		//列挙型の状態も変更
		m_CurrentState = state;
		break;
	case State::Die:
		//攻撃中なら攻撃判定を消す
		DeleteAttack();
		//現在の状態を死んだ状態に変更
		m_ActiveState = new BossDieState(this);
		//列挙型の状態も変更
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
	//RoorSoundの名前を見つけたら
	if (wcscmp(eventName, L"RoorSound") == 0) {
		//咆哮の音を出す
		m_RoarSound.Play();
		//咆哮時のエフェクトを流す
		Effect* m_Effect = NewGO<Effect>(0);
		m_Effect->Play(L"Assets/effect/BossRoar.efk");
		CVector3 RoarPos = m_ModelPos;
		//エフェクトの高さはモデルの半分の高さの位置にする
		RoarPos.y += height / 2;
		//エフェクトの位置を設定
		m_Effect->SetPosition(RoarPos);
		//エフェクトのスケールを設定
		m_Effect->SetScale(CVector3::One()*EffectScale);
	}
}

void Boss::InitSprite()
{
	//ボス用のHpを動的確保する
	m_BossSprite = NewGO< BossHpSprite>(0);
	//ボスのHpを設定する
	m_BossSprite->SetHp(m_MaxHp);
}
