#include "pch.h"
#include "Arrow.h"
#include "Archer.h"
#include "ArcherAttack.h"

namespace {
	const float MoveSpeed = 20.0f;
	const float DeleteTime = 10.0f;
}

void Arrow::Init(Archer* acr)
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Arrow.cmo");
	m_Archer = acr;
	m_ArcherAttack = NewGO<ArcherAttack>(0);
	m_ArcherAttack->SetPosition(m_Pos);
}

void Arrow::Update()
{
	//もしまだ発射していないなら
	if (!IsShot) {
		//もし弓にアタッチしないなら
		if (!m_Archer->IsAttachArrow()) {
			//指先をアタッチ方向にする
			m_Archer->CalcArrowPosAndRotationFromAttachBone(m_Pos, m_Rot, L"arrow_attach", L"arrow_attach_2");
		}
		else {
			//しないなら弓にアタッチする
			m_Archer->CalcArrowPosAndRotationFromAttachBone(m_Pos, m_Rot, L"arrow_attach", L"arrow_attach_3");
		}
	}
	else {
		//しないなら前方向を更新する
		CMatrix mRot;
		mRot.MakeRotationFromQuaternion(m_Rot);
		CVector3 Forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
		Forward.Normalize();
		//前方方向に飛ばす
		m_Pos += Forward * MoveSpeed;
	}
	m_ArcherAttack->SetPosition(m_Pos);
	//モデルの位置を更新
	m_Model->SetPosition(m_Pos);
	//モデルの回転を更新
	m_Model->SetRotation(m_Rot);
	m_ElapsedTime += gameTime().GetFrameDeltaTime();
	if (m_ElapsedTime > DeleteTime) {
		DeleteGO(this);
	}
}

void Arrow::OnDestroy()
{
	DeleteGO(m_Model);
	m_Archer->ArrowListPop();
}
