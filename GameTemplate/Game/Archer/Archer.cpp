#include "pch.h"
#include "Archer.h"
#include "State/ArcherIdleState.h"
#include "State/ArcherAttackState.h"
#include "Archer/Arrow.h"

namespace {
	//�X�v���C�g�̏c�̑傫��
	const float SpriteHight = 10.0f;
	//HP��������Ə�ɒu��
	const float HpPosUp = 30.0f;
	//�U���ł��锻��ɓ�����
	const float InPlayer = 500.0f;
	//����p
	const float ViewAngle = 0.7f;
	//�X�v���C�g�̊�_�����炵�Ă���̂�
	//���̃Y�����C��
	const float spriteFix = -50.0f;
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

bool Archer::Start()
{
	//�X�|�[���ʒu��ݒ�
	m_Position = m_SpownPositon;

	//���f����������
	InitModel();

	//�A�j���[�V������������
	InitAnimetion();

	//���݂̏�Ԃ�ҋ@��Ԃ�
	m_ActiveState = new ArcherIdleState(this);

	//�v���C���[��������
	m_Player = FindGO<Player>("player");

	//�G��������
	InitSprite();
	return true;
}

void Archer::InitModel()
{
	//���f����new
	m_Model = NewGO<SkinModelRender>(0);
	//���f�������[�h
	m_Model->Init(L"Assets/modelData/Archer.cmo");
	//���f���̈ʒu��ݒ�
	m_Model->SetPosition(m_Position);
	//���f���̉�]�ʂ�ݒ�
	m_Model->SetRotation(m_Rotation);
}

void Archer::InitAnimetion()
{
	//�e�A�j���[�V�����C�x���g�����[�h
	m_AnimationClip[State::Idle].Load(L"Assets/animData/ArcherIdle.tka");
	m_AnimationClip[State::Idle].SetLoopFlag(true);
	m_AnimationClip[State::Attack].Load(L"Assets/animData/ArcherAttack.tka");
	m_AnimationClip[State::Damage].Load(L"Assets/animData/ArcherDamage.tka");
	m_AnimationClip[State::Deth].Load(L"Assets/animData/ArcherDeth.tka");

	//�A�j���[�V������o�^
	m_Animation.Init(m_Model->GetModel(), m_AnimationClip, State::Num);
	//�C�x���g���X�i�[��o�^
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}

void Archer::InitSprite()
{
	//���Hp�o�[��������
	InitHpTop();
	//����Hp�o�[��������
	InitHpUnder();
}

void Archer::InitHpTop()
{
	//hp��new
	m_HpTopSprite = NewGO<SpriteRender>(2);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_Hp, SpriteHight, true);
	//�ʒu���X�V
	m_HpTopSprite->SetPosition(m_HpPosition);
	//�傫�����X�V
	m_HpTopSprite->SetScale(CVector3::One());
	//��_���X�V
	m_HpTopSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//�J���������ɉ摜��������
	m_HpTopSprite->SetIsFaceCamera(true);
}

void Archer::InitHpUnder()
{
	//Hp��New
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, SpriteHight, true);
	//�ʒu���X�V
	m_HpUnderSprite->SetPosition(m_HpPosition);
	//�傫�����X�V
	m_HpUnderSprite->SetScale(CVector3::One());
	//��_���X�V
	m_HpUnderSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//�J���������ɉ摜��������
	m_HpUnderSprite->SetIsFaceCamera(true);
}

void Archer::OnAnimEvent(const wchar_t * eventName)
{
	if (wcscmp(eventName, L"SpownArrow") == 0) {
		//������
		Arrow* m_Arrow = NewGO<Arrow>(0);
		//��̏�����
		m_Arrow->Init(this);
		m_ArrowList.push_back(m_Arrow);
	}
	if (wcscmp(eventName, L"bindArrow") == 0) {
		m_isAttachArrow = true;
	}
	if (wcscmp(eventName, L"ShotArrow") == 0) {
		m_ArrowList.back()->SetShot();
	}
	if(wcscmp(eventName, L"PlayerFacingFinish") == 0) {
		m_IsPlayerFacing = false;
	}
}


void Archer::CalcArrowPosAndRotationFromAttachBone(CVector3& pos, CQuaternion& rot, const wchar_t* AttchName, const wchar_t* TargetName)
{
	//��̃A�^�b�`�{�[�����擾�B
	Bone* attachBone = m_Model->GetModel().FindBone(AttchName);
	Bone* attachBone2 = m_Model->GetModel().FindBone(TargetName);
	//��������W�A��]�A�g�嗦���擾����B
	CVector3 posTmp;
	CQuaternion rotTmp;
	CVector3 scaleTmp;
	//arrow_attach�͖�̈ʒu�����߂邽�߂̍��B
	attachBone->CalcWorldTRS(pos, rotTmp, scaleTmp);
	//arrow_attach_2�͖�̌��������߂邽�߂̍��B
	attachBone2->CalcWorldTRS(posTmp, rotTmp, scaleTmp);

	//��̌������v�Z����B
	CVector3 dir = posTmp - pos;
	dir.Normalize();
	//��̉�]�N�H�[�^�j�I�����v�Z����B
	rot.SetRotation(CVector3::AxisZ(), dir);
}
void Archer::Update()
{
	//�A�j���[�V�������X�V
	AnimationUpdate();
	//�G���X�V
	UpdateSprite();
	//���݂̏�Ԃ̍X�V���Ă�
	m_ActiveState->Update();
	//��Ԃ��X�V
	UpdateState(m_NextState);
	//�O�����̍X�V
	ForwardUpdate();
	//���f���̍X�V
	ModelUpdate();
}

void Archer::AnimationUpdate()
{
	//���݂̃A�j���[�V�������Đ�������
	m_Animation.Play(m_State, 0.2f);
	//�A�j���[�V�������Đ�
	m_Animation.Update(gameTime().GetFrameDeltaTime());
}

bool Archer::IsAttack()
{
	if (GetAsyncKeyState('U')) {
		return true;
	}//�����̍��𑪂�
	CVector3 Diff = m_Player->GetPosition() - m_Position;
	//�����v���C���[���͈͓��ɂ���Ȃ�
	if (Diff.Length() < InPlayer) {
		Diff.Normalize();
		//�v���C���[�̕��������
		float Dir = m_Forward.Dot(Diff);
		//����ɓ����
		if (Dir > ViewAngle) {
			//�U���ł���
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
	m_HpUnderSprite->SetScale(SpriteSize);
	//Top�̈ʒu��ݒ�
	m_HpTopSprite->SetPosition(m_HpPosition);
	//Under�̈ʒu��ݒ�
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

void Archer::HpPosAdjustment()
{
	m_HpPosition.y += m_height + HpPosUp;
	CVector3 AddSpritePos = g_camera3D.GetRight() * spriteFix;
	m_HpPosition -= AddSpritePos;
}

void Archer::ForwardUpdate()
{
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rotation);
	m_Forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_Forward.Normalize();
}

void Archer::ModelUpdate()
{
	m_Model->SetPosition(m_Position);
	m_Model->SetRotation(m_Rotation);
}


void Archer::PlayerFacing()
{
	CVector3 NextForward = m_Player->GetPosition() - m_Position;
	float rotAngle = atan2(NextForward.x, NextForward.z);
	m_Rotation.SetRotation(CVector3::AxisY(), rotAngle);
}