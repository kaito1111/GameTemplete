#include "pch.h"
#include "Arrow.h"

namespace {
	const float MoveSpeed = 1.0f;
}

void Arrow::Init(CVector3 pos, CQuaternion rot)
{
	m_Position = pos;
	//ã|ÇÃë≈Ç¬çÇÇ≥Ç…í≤êÆ
	m_Rotation = rot;
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/Arrow.cmo");
	m_Model->SetPosition(m_Position);
	m_Model->SetRotation(m_Rotation);
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rotation);
	m_Forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_Forward.Normalize();

	m_AnimationClip[0].Load(L"Assets/animData/Arrow.tka");
	m_AnimationClip[0].SetLoopFlag(true);
	m_Animation.Init(m_Model->GetModel(), m_AnimationClip, 1);

}

void Arrow::Update()
{
	//m_Position += m_Forward * MoveSpeed;
	m_Model->SetPosition(m_Position);
	m_Animation.Update(gameTime().GetFrameDeltaTime());
}
