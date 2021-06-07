#include "pch.h"
#include "Archer.h"
#include "State/ArcherIdleState.h"
#include "State/ArcherAttackState.h"
#include "Archer/Arrow.h"
#include "State/ArcherDethState.h"

namespace {
	//�U���ł��锻��ɓ�����
	const float InPlayer = 500.0f;
	//����p
	const float ViewAngle = 0.7f;

	const float MaxHp = 62.5f;			//Hp
	const float m_height = 150.0f;  //�g��
	const float DethAlpha = 0.0f;
}

void Archer::OnDestroy()
{
	if (m_ActiveState != nullptr) {
		m_ActiveState = nullptr;
	}
	if (m_ArrowList.size() > 0) {
		auto list = m_ArrowList;
		for (auto i : list) {
			DeleteGO(i);
		}
	}
}

void Archer::HitDamage(const float damege) {
	//����łȂ��Ȃ�Hp�����炷
	if (m_ActiveState->IsPossibleHpDown()) {
		m_Hp -= damege;
	}
	//Hp��0�ȏ�Ȃ�_���[�W���[�V������
	if (m_Hp > 0) {
		m_NextState = State::Damage;
	}
	//�ȉ��Ȃ�hp��0�ɂ��ĎE��
	else {
		m_Hp = 0;
		m_NextState = State::Deth;
	}
}

bool Archer::Start()
{
	//�X�|�[���ʒu��ݒ�
	m_ModelPos = m_SpownPositon;

	//���f����������
	CharacterInit(L"Archer.cmo", 35.0f, 135.0f,m_ModelPos);

	//�A�j���[�V������������
	InitAnimetion();

	//���݂̏�Ԃ�ҋ@��Ԃ�
	m_ActiveState = new ArcherIdleState(this);

	//�v���C���[��������
	m_player = FindGO<Player>("player");

	//�G��������
	InitHpSprite(MaxHp,HpScale::EnemyHP);

	return true;
}

void Archer::InitModel()
{
	//���f����new
	m_Model = NewGO<SkinModelRender>(0);
	//���f�������[�h
	m_Model->Init(L"Archer.cmo");
	//���f���̈ʒu��ݒ�
	m_Model->SetPosition(m_ModelPos);
	//���f���̉�]�ʂ�ݒ�
	m_Model->SetRotation(m_ModelRot);
}

void Archer::InitAnimetion()
{
	//�e�A�j���[�V�����C�x���g�����[�h
	LoadAnimation(m_AnimationClip[State::Idle], L"ArcherIdle.tka");
	m_AnimationClip[State::Idle].SetLoopFlag(true);
	LoadAnimation(m_AnimationClip[State::Attack], L"ArcherAttack.tka");
	LoadAnimation(m_AnimationClip[State::Damage], L"ArcherDamage.tka");
	LoadAnimation(m_AnimationClip[State::Deth], L"ArcherDeth.tka");

	//�A�j���[�V������o�^
	InitAnimation(m_AnimationClip,State::Num);
	//�C�x���g���X�i�[��o�^
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}
void Archer::OnAnimEvent(const wchar_t * eventName)
{
	if (wcscmp(eventName, L"SpownArrow") == 0) {
		//������
		Arrow* m_Arrow = NewGO<Arrow>(0,"arrow");
		//��̏�����
		m_Arrow->Init(this);
		m_ArrowList.push_back(m_Arrow);
		m_HasArrow = m_Arrow;
	}
	if (wcscmp(eventName, L"bindArrow") == 0) {
		m_isAttachArrow = true;
	}
	if (wcscmp(eventName, L"ShotArrow") == 0) {
		m_ArrowList.back()->SetShot();
		m_HasArrow = nullptr;
	}
	if(wcscmp(eventName, L"PlayerFacingFinish") == 0) {
		m_IsPlayerFacing = false;
	}
}

void Archer::Rotate()
{
	CVector3 NextForward = m_player->GetPosition() - m_ModelPos;
	float rotAngle = atan2(NextForward.x, NextForward.z);
	m_ModelRot.SetRotation(CVector3::AxisY(), rotAngle);
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
	SpriteUpdate();
	//���݂̏�Ԃ̍X�V���Ă�
	m_ActiveState->Update();
	//��Ԃ��X�V
	UpdateState(m_NextState);
	//�O�����̍X�V
	ForwardUpdate();
	//���f���̍X�V
	CharacterModelUpdate();
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
	CVector3 Diff = m_player->GetPosition() - m_ModelPos;
	//�����v���C���[���͈͓��ɂ���Ȃ�
	if (Diff.Length() < InPlayer) {
		Diff.Normalize();
		//�v���C���[�̕��������
		float Dir = m_forward.Dot(Diff);
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
	case State::Idle:
		m_ActiveState = new ArcherIdleState(this);
		break;
	case State::Attack:
		m_ActiveState = new ArcherAttackState(this);
		break;
	case State::Deth:
		m_ActiveState = new ArcherDethState(this);
		m_CharaCon.RemoveRigidBoby();
		DeleteGO(m_HasArrow);
		m_HpUnderSprite->SetAlpha(DethAlpha);
		m_HasArrow = nullptr;
		break;
	case State::Damage:
		DeleteGO(m_HasArrow);
		m_HasArrow = nullptr;
		break;
	case State::Num:
		break;
	default:
		break;
	}
	m_State = st;
}