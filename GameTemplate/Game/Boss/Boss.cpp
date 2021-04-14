#include "Boss.h"

bool Boss::Start() {
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/Boss.cmo");
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Model->SetScale(CVector3::One()*1.8f);

	m_AnimationClip[Walk].Load(L"Assets/animData/BossDy.tka");
	m_Animation.Init(m_Model->GetModel(), m_AnimationClip, StateNum);
	return true;
}

void Boss::Update()
{
	m_Animation.Update(gameTime().GetFrameDeltaTime());
}
