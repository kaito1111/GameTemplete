#include "pch.h"
#include "Archer.h"
#include "State/ArcherIdleState.h"
#include "State/ArcherAttackState.h"
#include "Archer/Arrow.h"


bool Archer::Start()
{
	m_Position = m_SpownPositon;
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/Archer.cmo");
	m_Model->SetPosition(m_Position);
	m_Model->SetRotation(m_Rotation);
	//CVector3 m_Scale = CVector3::One()*10.0f;
	//m_Model->SetScale(m_Scale);

	m_AnimationClip[State::Idle].Load(L"Assets/animData/ArcherIdle.tka");
	m_AnimationClip[State::Idle].SetLoopFlag(true);
	m_AnimationClip[State::Attack].Load(L"Assets/animData/ArcherAttack.tka");
	m_AnimationClip[State::Damage].Load(L"Assets/animData/ArcherDamage.tka");
	m_AnimationClip[State::Deth].Load(L"Assets/animData/ArcherDeth.tka");

	m_Animation.Init(m_Model->GetModel(), m_AnimationClip, State::Num);
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnEventListener(clipName);
	});
	
	m_ActiveState = new ArcherIdleState(this);

	m_Player = FindGO<Player>("player");

	m_HpTopSprite = NewGO<SpriteRender>(0);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_Hp, 50.0f, true);
	//�ʒu���X�V
	m_HpTopSprite->SetPosition(m_HpPosition);
	//�傫�����X�V
	m_HpTopSprite->SetScale(CVector3::One());
	//��_���X�V
	m_HpTopSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//�J���������ɉ摜��������
	m_HpTopSprite->SetIsFaceCamera(true);

	//Hp��New
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, 50.0f, true);
	//�ʒu���X�V
	m_HpUnderSprite->SetPosition(m_HpPosition);
	//�傫�����X�V
	m_HpUnderSprite->SetScale(CVector3::One());
	//��_���X�V
	m_HpUnderSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//�J���������ɉ摜��������
	m_HpUnderSprite->SetIsFaceCamera(true);
	return true;
}

void Archer::Update()
{
	//m_Rotation.SetRotationDeg(CVector3::AxisX(), -90.0f);
	m_Animation.Play(m_State);
	m_Animation.Update(gameTime().GetFrameDeltaTime());
	m_ActiveState->Update();
	UpdateState(m_NextState);
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rotation);
	m_Forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_Forward.Normalize();
	m_Model->SetPosition(m_Position);
	m_Model->SetRotation(m_Rotation);
}

void Archer::OnDestroy()
{
	DeleteGO(m_Model);
	if (m_ActiveState != nullptr) {
		m_ActiveState = nullptr;
	}
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HpUnderSprite);
}

bool Archer::IsAttack()
{
	CVector3 Diff = m_Player->GetPosition() - m_Position;
	if (Diff.Length() < 500.0f) {
		Diff.Normalize();
		float Dir = m_Forward.Dot(Diff);
		if (Dir >0.7f) {
			return true;
		}
	}
	return false;
}

void Archer::UpdateState(int st)
{
	switch (st)
	{
	case Archer::Idle:
		m_ActiveState = new ArcherIdleState(this);
		break;
	case Archer::Attack:
		m_ActiveState = new ArcherAttackState(this);
		break;
	case Archer::Num:
		break;
	default:
		break;
	}
	m_State = st;
}

void Archer::UpdateSprite()
{
	//Hp�̈ʒu��G�̈ʒu�ɍ��킹��
	m_HpPosition = m_Position;
	HpPosAdjustment();
	//Hp�̑傫����hp�̎c�ʂɍ��킹��
	float SizeX = m_Hp * m_SpriteSize;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	//�傫����ݒ�
	m_HpTopSprite->SetScale(SpriteSize);
	//Top�̈ʒu��ݒ�
	m_HpTopSprite->SetPosition(m_HpPosition);
	//Under�̈ʒu��ݒ�
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

void Archer::HpPosAdjustment()
{
	//HP��������Ə�ɒu��
	const float HpPosUp = 10.0f;
	m_HpPosition.y += m_height + HpPosUp;
	//��_�����炵�Ă���̂�
	//���̃Y�����C��
	CVector3 AddSpritePos = g_camera3D.GetRight()*-50.0f;
	m_HpPosition -= AddSpritePos;
}

void Archer::OnEventListener(const wchar_t * clipName)
{
	if (wcscmp(clipName, L"SpownArrow") == 0) {
		Arrow* arrow = NewGO<Arrow>(0);
		arrow->Init(m_Position, m_Rotation);

	}
}
