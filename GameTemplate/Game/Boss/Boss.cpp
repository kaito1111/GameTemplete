#include "Boss.h"
#include "Player/Player.h"
#include "State/BossAppearanceRoarState.h"
#include "State/BossAttackState.h"
#include "State/BossDieState.h"
#include "State/BossWalkState.h"
#include "State/BossNormalRoar.h"
#include "State/IBossState.h"

namespace {
	const float radius = 60.0f;
	const float hight = 60.0f;
	const float modelScale = 1.8f;
	const float InPlayer = 50.0f;
}

bool Boss::Start() {

	m_AnimationClip[State::Walk].Load(L"Assets/animData/BossWalk.tka");
	m_AnimationClip[State::Walk].SetLoopFlag(true);
	m_AnimationClip[State::Attack].Load(L"Assets/animData/BossAttack.tka");
	m_AnimationClip[State::AppearanceRoar].Load(L"Assets/animData/BossAppearanceRoar.tka");
	m_AnimationClip[State::NormalRoar].Load(L"Assets/animData/BossNormalRoar.tka");
	m_AnimationClip[State::Die].Load(L"Assets/animData/BossDie.tka");
	m_Animation.Init(m_Model->GetModel(), m_AnimationClip, StateNum);
	
	m_player = FindGO<Player>("player");

	m_CharaCon.Init(radius, hight, m_Pos);

	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"Assets/modelData/DebugShere.cmo");
	//z�̓��[���h��Ԃł̂��ɂ�����
	//y�͍l�����Ȃ�
	m_HitModel->SetScale({ radius, radius, 1.0f });
	return true;
}

void Boss::ModelInit()
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/Boss.cmo");
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Model->SetScale(CVector3::One()*modelScale);
}

void Boss::Update()
{
	ChengeState(m_NextState);
	m_ActiveState->Update();
}

void Boss::IsChengeAttackState()
{
	CVector3 Diff = m_player->GetPosition() - m_Pos;
	if (Diff.Length() < InPlayer) {
		m_NextState = State::Attack;
	}
}

void Boss::Move(CVector3& move)
{
	//��]�̍X�V
	Rotate();
	//�����蔻������s
	m_Pos = m_CharaCon.Execute(gameTime().GetFrameDeltaTime(), move);
	//���f���̈ʒu��ݒ�
	m_Model->SetPosition(m_Pos);
	//���f���̉�]��ݒ�
	m_Model->SetRotation(m_Rot);
}
void Boss::IsChengeNormalRoar()
{
	m_RoarTime += gameTime().GetFrameDeltaTime();
	if (m_RoarTime > m_CoolTimeRoar) {
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
		break;
	case State::NormalRoar:
		m_ActiveState = new BossNormalRoar(this);
		m_CurrentState = state;
		break;
	default:
		break;
	}
}

void Boss::Rotate()
{
	//�v���C���[�Ƃ̋����𑪂�
	CVector3 diff = m_player->GetPosition() - m_Pos;
	//�����̕������g���ĉ�]�ʂ����߂�
	float angle = atan2(diff.x, diff.z);
	//��]�ʂ�ۑ�
	m_Rot.SetRotation(CVector3::AxisY(), angle);
	//�O�������X�V
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rot);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_forward.Normalize();
}
