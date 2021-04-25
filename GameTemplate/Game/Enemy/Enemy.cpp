#include "pch.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Enemy/State/EnemyAttackState.h"
#include "Enemy/State/EnemyIdleState.h"
#include "Enemy/State/EnemyWalkState.h"
#include "Enemy/State/IEnemyState.h"
#include "Enemy/State/EnemyDamageState.h"
#include "State/EnemyDown.h"
#include "EnemyAttack.h"

namespace {
	
	const float visility = 500.0f;//視界	
	const float radius = 20.0f;//キャラコンの幅
	const float m_height = 150.0f;				//敵の身長
	const float hpSpriteSizeY = 10.0f;	//スプライトの縦幅
	const float AttackDamage = 10.0f;	//攻撃力
	const float AttackEria = 135.0f;	//攻撃範囲
	const float  SpriteClear = 0.0f;	//スプライトを透明にする	
}
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::OnDestroy()
{
	//この敵に関係するインスタンスを削除
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HpUnderSprite);
}


void Enemy::HitDamege(const float damege) {
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
	m_ModelScale *= 10.0f;
	//プレイヤーのポインタを見つける
	m_Player = FindGO<Player>("player");
	//初期位置を設定
	m_ModelPos = m_SpownPosition;

	//モデルとキャラコンを初期化
	CharacterInit(L"Skeleton.cmo", radius, m_height, m_ModelPos);

	//HPのスプライトを初期化
	HpSpriteInit();

	//アニメーションを初期化
	AnimetionInit();

	//初期化でIdleStateを設定
	m_ActiveState = new EnemyIdleState(this);

	return true;
}

void Enemy::HpSpriteInit()
{
	//hpスプライトを設定
	m_HpPosition = m_ModelPos;
	//スプライトのサイズを設定
	CVector3 SpriteSize = CVector3::One();
	//float sizeX = m_SpriteSize * m_Hp;
	//SpriteSize.x = sizeX;
	//TopSpriteを初期化
	HpTopSpriteInit(hpSpriteSizeY, SpriteSize);
	//UnderSpriteを初期化
	HpUnderSprite(hpSpriteSizeY, SpriteSize);
}


void Enemy::HpTopSpriteInit(const float SizeY, const CVector3& Scale)
{
	//HpをNew
	m_HpTopSprite = NewGO<SpriteRender>(2);
	//Hpをロード、画像の大きさも設定
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", 86.0f , SizeY, true);
	//位置を更新
	m_HpTopSprite->SetPosition(m_HpPosition);
	//大きさを更新
	m_HpTopSprite->SetScale(Scale);
	//基点を更新
	m_HpTopSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//カメラ方向に画像を向ける
	m_HpTopSprite->SetIsFaceCamera(true);
}

void Enemy::HpUnderSprite(const float SizeY, const CVector3& Scale)
{
	//HpをNew
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	//Hpをロード、画像の大きさも設定
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, SizeY, true);
	//位置を更新
	m_HpUnderSprite->SetPosition(m_HpPosition);
	//大きさを更新
	m_HpUnderSprite->SetScale(Scale);
	//基点を更新
	m_HpUnderSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//カメラ方向に画像を向ける
	m_HpUnderSprite->SetIsFaceCamera(true);
}

void Enemy::AnimetionInit()
{
	//アニメーションをロード
	m_AniClip[State::Walk].Load(L"Assets/AnimData/SkeltonWalk.tka");
	//ループフラグを有効
	m_AniClip[State::Walk].SetLoopFlag(true);
	m_AniClip[State::Attack].Load(L"Assets/AnimData/SkeltonAttack.tka");
	m_AniClip[State::Damege].Load(L"Assets/AnimData/SkeltonDamage.tka");
	m_AniClip[State::Down].Load(L"Assets/AnimData/SkeltonDown.tka");
	m_AniClip[State::Idle].Load(L"Assets/AnimData/SkeltonIdle.tka");

	//ループフラグを有効
	m_AniClip[State::Idle].SetLoopFlag(true);
	//アニメーションを設定
	m_Animation.Init(m_Model->GetModel(), m_AniClip, State::Num);
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
		DeleteGO("enemyAttack");
	}
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
		//CreateEnemyAttack();
		break;
	case State::Damege:		//攻撃をくらった
		delete m_ActiveState;
		DeleteGOs("enemyAttack");
		m_ActiveState = new EnemyDamageState(this);
		break;
	case State::Down:		//死んだ
		delete m_ActiveState;
		DeleteGOs("enemyAttack");
		m_CharaCon.RemoveRigidBoby();
		m_HpUnderSprite->SetAlpha(SpriteClear);
		m_ActiveState = new EnemyDown(this);
	}
	m_State = st;
}

void Enemy::Update()
{
	//スプライトを更新
	UpdateSprite();
	//ステートを更新
	m_ActiveState->Update();
	//ステートを変更する
	ChangeState(m_NextState);
	//アニメーションを更新
	m_Animation.Update(gameTime().GetFrameDeltaTime());
	CharacterModelUpdate();
}

void Enemy::UpdateSprite()
{
	//Hpの位置を敵の位置に合わせる
	m_HpPosition = m_ModelPos;
	HpPosAdjustment();
	////Hpの大きさをhpの残量に合わせる
	//float SizeX = m_Hp * m_SpriteSize;
	//CVector3 SpriteSize = CVector3::One();
	//SpriteSize.x = SizeX;
	////大きさを設定
	//m_HpTopSprite->SetScale(SpriteSize);
	//Topの位置を設定
	m_HpTopSprite->SetPosition(m_HpPosition);
	//Underの位置を設定
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

void Enemy::HpPosAdjustment()
{
	//HPをちょっと上に置く
	const float HpPosUp = 10.0f;
	m_HpPosition.y += m_height + HpPosUp;
	//基点をずらしているので
	//そのズレを修正
	CVector3 AddSpritePos = g_camera3D.GetRight()*-50.0f;
	m_HpPosition -= AddSpritePos;
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
