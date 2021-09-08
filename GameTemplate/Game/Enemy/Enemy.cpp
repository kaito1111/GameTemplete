#include "pch.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Enemy/State/EnemyAttackState.h"
#include "Enemy/State/EnemyIdleState.h"
#include "Enemy/State/EnemyWalkState.h"
#include "Enemy/State/IEnemyState.h"
#include "Enemy/State/EnemyDamageState.h"
#include "State/EnemyDown.h"
#include "GameSceneFunction/AIProcesing.h"
#include "GameSceneFunction/Attack.h"

namespace {
	const float visility = 500.0f;//視界	
	const float radius = 20.0f;//キャラコンの幅
	const float m_height = 150.0f;				//敵の身長
	const float hpSpriteSizeY = 10.0f;	//スプライトの縦幅
	const float AttackDamage = 10.0f;	//攻撃力
	const float AttackEria = 135.0f;	//攻撃範囲
	const float SpriteClear = 0.0f;	//スプライトを透明にする
	const float SpriteSize = 0.025f;			//hpのサイズを調整	
	const float EnemyMaxHp = 62.5;
	const float EnemyScale = 4.5f;
}

void Enemy::HitDamage(const float damege) {
	//死んでないならHpを減らす
	if (m_ActiveState->IsPossibleHpDown()) {
		m_Hp -= damege;
	}
	//Hpが0以上ならダメージモーションを
	if (m_Hp > 0) {
		m_NextState = State::Damege;
	}
	//以下ならhpを0にして殺す
	else {
		m_Hp = 0;
		m_NextState = State::Down;
	}
}

bool Enemy::Start()
{
	//モデルの大きさを調整
	m_ModelScale *= EnemyScale;
	//プレイヤーのポインタを見つける
	m_Player = FindGO<Player>("player");

	//モデルとキャラコンを初期化
	CharacterInit(L"Skeleton.cmo", radius, m_height, m_ModelPos);

	m_Hp = EnemyMaxHp;
	//HPのスプライトを初期化
	InitHpSprite(EnemyMaxHp,m_Hp);

	//アニメーションを初期化
	AnimetionInit();

	//初期化でIdleStateを設定
	m_ActiveState = new EnemyIdleState(this);
	m_WalkSound.Init(L"EnemyWalk.wav");
	m_SwingSound.Init(L"EnemySwingSword.wav");
	//m_WalkSound.Play(true);
	//m_WalkSound.SetVolume(0.0f);
	m_Model->SetAmbientColor(0.4f);

	m_AttackVoice.Init(L"EnemyAttackVoice.wav"); 
	m_AttackVoice.SetVolume(3.0f);
	return true;
}
void Enemy::OnDestroy()
{
	Destroy();
	if (m_ActiveState != nullptr) {
		delete m_ActiveState;
	}
}
void Enemy::AnimetionInit()
{
	//アニメーションをロード
	LoadAnimation(m_AniClip[State::Walk], L"SkeltonWalk.tka");
	//ループフラグを有効
	m_AniClip[State::Walk].SetLoopFlag(true);
	LoadAnimation(m_AniClip[State::Attack],L"SkeltonAttack.tka");
	LoadAnimation(m_AniClip[State::Damege],L"SkeltonDamage.tka");
	LoadAnimation(m_AniClip[State::Down], L"SkeltonDown.tka");
	LoadAnimation(m_AniClip[State::Idle], L"SkeltonIdle.tka");
	//ループフラグを有効
	m_AniClip[State::Idle].SetLoopFlag(true);
	//アニメーションを設定
	InitAnimation(m_AniClip, State::Num);
	//イベントリスナーを設定
	m_Animation.AddAnimationEventListener([&](const wchar_t* ClipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}

void Enemy::OnAnimEvent(const wchar_t* eventName)
{
	//AttackStartの名前を見つけたら
	if (wcscmp(eventName, L"AttackStart") == 0) {
		//攻撃判定を作る
		AIAttack(AttackDamage, AttackEria, "enemyAttack");
	}
	//AttackEndの名前を見つけたら
	if (wcscmp(eventName, L"AttackEnd") == 0) {
		//攻撃判定を消す
		DeleteAttack();
	}
	if (wcscmp(eventName, L"WalkSound1") == 0) {
		m_WalkSound.Play();
	}
	if (wcscmp(eventName, L"WalkSound2") == 0) {
		m_WalkSound.Play();
	}
	if (wcscmp(eventName, L"AttackVoice") == 0) {
		m_AttackVoice.Play();
	}
	//if (wcscmp(eventName, L"SwingSound") == 0) {
	//	m_WalkSound.Play();
	//}
}

void Enemy::ChangeState(int st)
{
	//引数で渡されたステートのインスタンスを作成。
	switch (st) {
	case State::Idle:		//待機中
		if (m_ActiveState != nullptr) {
			delete m_ActiveState;
		}
		m_ActiveState = new EnemyIdleState(this);
		break;
	case State::Walk:		//走り中
		delete m_ActiveState;
		m_ActiveState = new EnemyWalkState(this);
		break;
	case State::Attack:		//攻撃中
		delete m_ActiveState;
		m_ActiveState = new EnemyAttackState(this);
		break;
	case State::Damege:		//攻撃をくらった
		delete m_ActiveState;
		DeleteAttack();
		m_ActiveState = new EnemyDamageState(this);
		break;
	case State::Down:		//死んだ
		delete m_ActiveState;
		DeleteAttack();
		m_CharaCon.RemoveRigidBoby();
		m_HpUnderSprite->SetAlpha(SpriteClear);
		m_ActiveState = new EnemyDown(this);
	}
	m_State = st;
}

void Enemy::Update()
{
	//スプライトを更新
	SpriteUpdate();
	//ステートを更新
	m_ActiveState->Update();
	//ステートを変更する
	ChangeState(m_NextState);
	//前方向の更新
	ForwardUpdate();
	//アニメーションを更新
	m_Animation.Update(gameTime().GetFrameDeltaTime());
	//モデルを移動
	CharacterModelUpdate();
	//hpが見えるかどうか
	UpdateHpAlpha();
}

bool Enemy::IsWalk() const
{
	//プレイヤーとの距離を判定
	CVector3 Diff = m_Player->GetPosition() - m_ModelPos;
	//もしプレイヤーが視界内なら
	if (Diff.Length() < visility) {
		Diff.Normalize();
		//プレイヤーが目の前から何度回っているか測る
		float ViewAngle = m_forward.Dot(Diff);
		//敵の視野角
		const float fieldView = 0.7f;
		//視野内に入った
		if (ViewAngle > fieldView) {
			return true;
		}
	}
	return false;
}
bool Enemy::IsAttack() const
{
	//プレイヤーとの距離を比較
	CVector3 Diff = m_Player->GetPosition() - m_ModelPos;
	//攻撃をすると判断する範囲
	//攻撃の範囲ではない
	const float AttackRenge = 100.0f;
	//攻撃範囲に入った
	if (Diff.Length() < AttackRenge) {
		//プレイヤーから前方向から何℃回っているか
		float ViewAngle = m_forward.Dot(Diff);
		//視野角
		const float fieldView = 0.7f;
		//視界内に入った
		if (ViewAngle > fieldView) {
			return true;
		}
	}
	//見つからなかった
	return false;
}

void Enemy::Rotate()
{
	//向く位置との距離を測る
	CVector3 diff = m_Player->GetPosition() - m_ModelPos;
	//距離の方向を使って回転量を求める
	float angle = atan2(diff.x, diff.z);
	//回転量を保存
	m_ModelRot.SetRotation(CVector3::AxisY(), angle);
	//前方向を更新
	ForwardUpdate();
}
