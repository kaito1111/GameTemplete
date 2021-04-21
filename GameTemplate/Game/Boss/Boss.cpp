#include "Boss.h"
#include "Player/Player.h"
#include "State/BossAppearanceRoarState.h"
#include "State/BossAttackState.h"
#include "State/BossDieState.h"
#include "State/BossWalkState.h"
#include "State/BossNormalRoar.h"
#include "State/IBossState.h"

bool Boss::Start() {
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/Boss.cmo");
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Model->SetScale(CVector3::One()*1.8f);

	m_AnimationClip[State::Walk].Load(L"Assets/animData/BossWalk.tka");
	m_AnimationClip[State::Walk].SetLoopFlag(true);
	m_AnimationClip[State::Attack].Load(L"Assets/animData/BossAttack.tka");
	m_AnimationClip[State::AppearanceRoar].Load(L"Assets/animData/BossAppearanceRoar.tka");
	m_AnimationClip[State::NormalRoar].Load(L"Assets/animData/BossNormalRoar.tka");
	m_AnimationClip[State::Die].Load(L"Assets/animData/BossDie.tka");
	m_Animation.Init(m_Model->GetModel(), m_AnimationClip, StateNum);
	
	m_player = FindGO<Player>("player");
	return true;
}

void Boss::Update()
{
	ChengeState(m_NextState);
	m_ActiveState->Update();
}

void Boss::IsChengeAttackState()
{
	CVector3 Diff = m_player->GetPosition() - m_Pos;
	if (Diff.Length() < 50.0f) {
		m_NextState = State::Attack;
	}
}

void Boss::IsChengeNormalRoar()
{
	m_RoarTime += gameTime().GetFrameDeltaTime();
	if (m_RoarTime > m_CoolTimeRoar) {
		m_NextState = State::NormalRoar;
	}
}

void Boss::ChengeState(State state)
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
		break;
	case State::NormalRoar:
		m_ActiveState = new BossNormalRoar(this);
		m_CurrentState = state;
		break;
	default:
		break;
	}
}
