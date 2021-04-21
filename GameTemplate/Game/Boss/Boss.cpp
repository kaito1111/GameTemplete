#include "Boss.h"

bool Boss::Start() {
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/Boss.cmo");
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Model->SetScale(CVector3::One()*1.8f);

	m_AnimationClip[State::Walk].Load(L"Assets/animData/BossWalk.tka");
	m_AnimationClip[State::Walk].SetLoopFlag(true);
	m_AnimationClip[State::Attack].Load(L"Assets/animData/BossAttack.cmo");
	m_AnimationClip[State::AppearanceRoar].Load(L"Assets/animData/BossAppearanceRoar.tka");
	m_AnimationClip[State::NormalRoar].Load(L"Assets/animData/BossNormalRoar.tka");
	m_AnimationClip[State::Die].Load(L"Assets/animData/BossDie.tka");
	m_Animation.Init(m_Model->GetModel(), m_AnimationClip, StateNum);
	return true;
}

void Boss::Update()
{
	m_Animation.Update(gameTime().GetFrameDeltaTime());
}
