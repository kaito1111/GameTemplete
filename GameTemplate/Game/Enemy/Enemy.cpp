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

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::OnDestroy()
{
	DeleteGO(m_Skin);
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HpUnderSprite);
}

void Enemy::Move(CVector3 move)
{
	EnemyRot();
	m_Pos = m_CharaCon.Execute(1.0f / 60.0f, move);
}
void Enemy::HitDamege(float damege) {
	if (m_ActiveState->IsPossibleHpDown()) {
		m_Hp -= damege;
	}
	if (m_Hp > 0) {
		m_NextState = State::Damege;
	}
	else {
		m_Hp = 0;
		m_NextState = State::Down;
	}
}
bool Enemy::Start()
{
	m_Player = FindGO<Player>("player");
	m_Pos = m_SpownPosition;

	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"Assets/modelData/keleton.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetRotation(m_Rot);
	m_Skin->SetScale(m_Scale);
	m_Skin->SetRenderMode(1);

	const float radius = 20.0f;
	m_CharaCon.Init(radius, m_height, m_Pos);

	const float hpSpriteSizeY = 10.0f;
	float sizeX = m_SpriteSize * m_Hp;
	m_HpTopSprite = NewGO<SpriteRender>(2);
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_Hp, hpSpriteSizeY, true);
	m_HpPosition = m_Pos;
	//HPをちょっと上に置く
	const float HpPosUp = 10.0f;
	m_HpPosition.y += m_height + HpPosUp;
	//基点をずらしているので
	//そのズレを修正
	CVector3 AddSpritePos = g_camera3D.GetRight()*-50.0f;
	m_HpPosition -= AddSpritePos;
	m_HpTopSprite->SetPosition(m_HpPosition);
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = sizeX;
	m_HpTopSprite->SetScale(SpriteSize);
	m_HpTopSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, hpSpriteSizeY, true);
	m_HpUnderSprite->SetPosition(m_HpPosition);
	m_HpUnderSprite->SetScale(SpriteSize);
	m_HpUnderSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	m_HpUnderSprite->SetIsFaceCamera(true); 
	m_HpTopSprite->SetIsFaceCamera(true);

	m_AniClip[State::Walk].Load(L"Assets/AnimData/SkeltonWalk.tka");
	m_AniClip[State::Walk].SetLoopFlag(true);
	m_AniClip[State::Attack].Load(L"Assets/AnimData/SkeltonAttack.tka");
	m_AniClip[State::Damege].Load(L"Assets/AnimData/SkeltonDamage.tka");
	m_AniClip[State::Down].Load(L"Assets/AnimData/SkeltonDown.tka");
	m_AniClip[State::Idle].Load(L"Assets/AnimData/SkeltonIdle.tka");
	m_AniClip[State::Idle].SetLoopFlag(true);
	m_Animation.Init(m_Skin->GetModel(), m_AniClip, State::Num);
	m_Animation.AddAnimationEventListener([&](const wchar_t* ClipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});

	m_ActiveState = new EnemyIdleState(this);

	return true;
}
void Enemy::OnAnimEvent(const wchar_t* eventName)
{
	if (wcscmp(eventName, L"AttackStart") == 0) {
		attack = NewGO< EnemyAttack>(0, "enemyAttack");
		const float AttackDamage = 10.0f;
		const float AttackEria = 135.0f;
		attack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"AttackEnd") == 0) {
		DeleteGO("enemyAttack");
	}
}

void Enemy::ChangeState(int st)
{
	//引数で渡されたステートのインスタンスを作成。
	switch (st) {
	case State::Idle:
		if (m_ActiveState != nullptr) {
			delete m_ActiveState;
		}
		m_ActiveState = new EnemyIdleState(this);
		break;
	case State::Walk:		//走り中
		delete m_ActiveState;
		m_ActiveState = new EnemyWalkState(this);
		break;
	case State::Attack:
		delete m_ActiveState;
		m_ActiveState = new EnemyAttackState(this);
		//CreateEnemyAttack();
		break;
	case State::Damege:
		delete m_ActiveState;
		DeleteGOs("enemyAttack");
		m_ActiveState = new EnemyDamageState(this);
		break;
	case State::Down:
		delete m_ActiveState;
		DeleteGOs("enemyAttack");
		m_ActiveState = new EnemyDown(this);
	}
	m_State = st;
}

void Enemy::Update()
{
	UpdateSprite();
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetRotation(m_Rot);
	//if (m_AttackPattarn == 1) {
	//	m_EnemyAttack = NewGO<EnemyAttack>(0);
	//	m_EnemyAttack->Init(20.0f, 20.0f, m_Pos, 0.0f);
	//}
	//if (g_pad[0].IsPress(enButtonA)) {
	//	m_Animation.Play(State::Attack);
	//}
	//if (g_pad[0].IsPress(enButtonB)) {
	//	m_Animation.Play(State::Walk);
	//}
	//if (g_pad[0].IsPress(enButtonX)) {
	//	m_Animation.Play(State::Damege);
	//}
	m_ActiveState->Update();
	if (m_NextState != m_State) {
		ChangeState(m_NextState);
	}
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_Rot);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_forward.Normalize();
	//攻撃の肩から腕までの距離
	const float AttackReach = 100.0f;
	m_AttackPos = m_Pos + m_forward * AttackReach;
	m_Animation.Update(1.0f / 60.0f);
}

void Enemy::EnemyRot()
{
	CVector3 diff = m_Player->GetPosition() - m_Pos;
	float angle = atan2(diff.x, diff.z);
	m_Rot.SetRotation(CVector3::AxisY(), angle);
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rot);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_forward.Normalize();
}

void Enemy::UpdateSprite()
{
	m_HpPosition = m_Pos;
	//HPをちょっと上に置く
	m_HpPosition.y += m_height + 10.0f;
	float SizeX = m_Hp * m_SpriteSize;
	//基点をずらしているので
	//そのズレを修正
	CVector3 AddSpritePos = g_camera3D.GetRight()*-50.0f;
	m_HpPosition -= AddSpritePos;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	m_HpTopSprite->SetScale(SpriteSize);
	m_HpTopSprite->SetPosition(m_HpPosition);
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

bool Enemy::IsWalk() const
{
	CVector3 Diff = m_Player->GetPosition() - m_Pos;
	//視界
	const float visility = 500.0f;
	if (Diff.Length() < visility) {
		Diff.Normalize();
		float ViewAngle = m_forward.Dot(Diff);
		const float fieldView = 0.7f;
		if (ViewAngle > fieldView) {
			return true;
		}
	}
	return false;
}
bool Enemy::IsAttack() const
{
	CVector3 Diff = m_Player->GetPosition() - m_Pos;
	const float AttackRenge = 100.0f;
	if (Diff.Length() < AttackRenge) {
		float ViewAngle = m_forward.Dot(Diff);
		const float fieldView = 0.7f;
		if (ViewAngle > fieldView) {
			return true;
		}
	}
	return false;
}

bool Enemy::IsDamage() const
{
	if (m_State != State::Damege) {
		return true;
	}
}

void Enemy::CreateEnemyAttack() {
	//EnemyAttack* Attack = NewGO< EnemyAttack>(0);
}
