#include "pch.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Enemy/State/EnemyAttackState.h"
#include "Enemy/State/EnemyIdleState.h"
#include "Enemy/State/EnemyWalkState.h"
#include "Enemy/State/IEnemyState.h"
#include "Enemy/State/EnemyDamageState.h"
#include "EnemyAttack.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Move(CVector3 move)
{
	EnemyRot();
	m_Pos = m_CharaCon.Execute(1.0f / 60.0f, move);
}

bool Enemy::Start()
{
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"Assets/modelData/keleton.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetRotation(m_Rot);
	m_Skin->SetScale(m_Scale);
	m_Skin->SetRenderMode(1);

	m_CharaCon.Init(20.0f, m_height, m_Pos);

	m_HpTopSprite = NewGO<SpriteRender>(2);
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_Hp, 10.0f, true);
	m_HpPosition = m_Pos;
	m_HpPosition.y += m_height + 10.0f;
	m_HpTopSprite->SetPosition(m_HpPosition);
	//m_HpTopSprite->SetPivot({ -1.0f,0.0f });
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, 10.0f, true);
	m_HpUnderSprite->SetPosition(m_HpPosition);

	m_AniClip[State::Walk].Load(L"Assets/AnimData/SkeltonWalk.tka");
	m_AniClip[State::Walk].SetLoopFlag(true);
	m_AniClip[State::Attack].Load(L"Assets/AnimData/SkeltonAttack.tka");
	m_AniClip[State::Damege].Load(L"Assets/AnimData/SkeltonDamage.tka");
	m_AniClip[State::Idle].Load(L"Assets/AnimData/SkeltonIdle.tka");
	m_AniClip[State::Idle].SetLoopFlag(true);
	m_Animation.Init(m_Skin->GetModel(), m_AniClip, State::Num);

	m_ActiveState = new EnemyIdleState(this);
	return true;
}
void Enemy::OnAnimEvent(const wchar_t* eventName)
{
	if (wcscmp(eventName, L"AttackEnd1") == 0) {
		m_AttackPattarn = 1;

	}
	if (wcscmp(eventName, L"AttackEnd2") == 0) {
		m_AttackPattarn = 0;
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
		CreateEnemyAttack();
		break;
	case State::Damege:
		delete m_ActiveState;
		m_ActiveState = new EnemyDamageState(this);
		break;
	}

	m_State = st;
}

void Enemy::Update()
{
	m_Mutekiframe--;
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
	m_HpPosition.y += m_height + 10.0f;
	float SizeX = m_Hp * m_SpriteSize;
	m_HpPosition.x -= 50.0f;
	m_HpTopSprite->SetScale({ SizeX,1.0f,1.0f });
	m_HpTopSprite->SetPosition(m_HpPosition);
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

bool Enemy::IsWalk() const
{
	CVector3 Diff = m_Player->GetPosition() - m_Pos;
	if (Diff.Length() < 500.0f) {
		Diff.Normalize();
		float ViewAngle = m_forward.Dot(Diff);
		if (ViewAngle > 0.7f) {
			return true;
		}
	}
	return false;
}
bool Enemy::IsAttack() const
{
	CVector3 Diff = m_Player->GetPosition() - m_Pos;
	if (Diff.Length() < 100.0f) {
		return true;
	}
	return false;
}

bool Enemy::IsDamage() const
{
	return false;
}

void Enemy::CreateEnemyAttack() {
	EnemyAttack* Attack = NewGO< EnemyAttack>(0);
	Attack->Init(10.0f, 50.0f, m_Pos, 60);
}
