#include "Boss.h"
#include "Player/Player.h"
#include "State/BossAppearanceRoarState.h"
#include "State/BossAttackState.h"
#include "State/BossDieState.h"
#include "State/BossWalkState.h"
#include "State/BossNormalRoar.h"
#include "State/IBossState.h"
#include "GameSceneFunction/Attack.h"

namespace {
	const float radius = 60.0f;		//�L�����R���̕�
	const float height = 130.0;		//�L�����R���̍���
	const float modelScale = 1.8f;	//���f���̑傫��
	const float InPlayer = 200.0f;	//�v���C���[���U���͈͓��ɂ��邩�ǂ����Ɏg��
	const float Damage = 15.0f;		//�_���[�W
	const float Eria = 70.0f;		//�U���͈�
	const float BossMaxHp = 300.0f;	//�{�X�ő��HP
	const float HpSpriteSizeX = 1.5625f;

	const float hpSpriteSizeY = 10.0f;	//�X�v���C�g�̏c��
	//const float HpSpriteSizeX = 1.5625f;
	//�X�v���C�g�̊�_�����炵�Ă���̂�
	//���̃Y�����C��
	const float spriteFix = -50.0f;
	float Hight = 0.0f;
	//HP��������Ə�ɒu��
	const float HpPosUp = 30.0f;
	const float HpSpriteDead = 0.0f;//�{�X�����񂾂Ƃ���Hp�o�[�������Ȃ�����
}

bool Boss::Start() {
	m_ModelPos = m_SpownPosition;
	CharacterInit(L"Boss.cmo", radius, height, m_ModelPos);
	AnimationInit();
	m_player = FindGO<Player>("player");
	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"DebugShere.cmo");
	//z�̓��[���h��Ԃł̂��ɂ�����
	//y�͍l�����Ȃ�
	m_HitModel->SetScale({ radius, radius, 1.0f });
	AttackReach = 150.0f;

	InitHpSprite(BossMaxHp, HpScale::BossHP);
	InitSprite();
	m_RoarSound.Init(L"RoarSound.wav");
	m_HpTopSprite->SetAlpha(0.0f);
	m_HpUnderSprite->SetAlpha(0.0f);
	return true;
}

void Boss::Update()
{
	//��Ԃ�ύX
	ChengeState(m_NextState);
	//���݂̏�Ԃ��X�V
	m_ActiveState->Update();
	//Animation���v���C
	m_Animation.Play(m_CurrentState);
	//���K���X�V
	RoarUpdate();
	//Boss�p�̃X�v���C�g��Hp��ݒ�
	m_BossSprite->SetHp(m_Hp);
	//Charactor�N���X��Hp�o�[�̍X�V
	SpriteUpdate();
	//�O�������X�V
	ForwardUpdate();
}

void Boss::OnDestroy()
{
	DeleteGO(m_HitModel);
	DeleteGO(m_BossSprite);
}

void Boss::IsChengeAttackState()
{
	CVector3 Diff = m_player->GetPosition() - m_ModelPos;
	if (Diff.Length() < InPlayer) {
		m_NextState = State::Attack;
	}
}

void Boss::IsChengeNormalRoar()
{
	m_RoarTime += gameTime().GetFrameDeltaTime();
	if (m_RoarTime > m_CoolTimeRoar) {
		m_RoarTime = 0;
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
		DeleteGO(m_HaveAttack);
		m_HaveAttack = nullptr;
		break;
	case State::NormalRoar:
		m_ActiveState = new BossNormalRoar(this);
		DeleteGO(m_HaveAttack);
		m_HaveAttack = nullptr;
		m_CurrentState = state;
		break;
	case State::Die:
		m_ActiveState = new BossDieState(this);
		m_HpUnderSprite->SetAlpha(HpSpriteDead);
		m_CurrentState = state;
	default:
		break;
	}
}

void Boss::Rotate()
{
	//�v���C���[�Ƃ̋����𑪂�
	CVector3 diff = m_player->GetPosition() - m_ModelPos;
	//�����̕������g���ĉ�]�ʂ����߂�
	float angle = atan2(diff.x, diff.z);
	//��]�ʂ�ۑ�
	m_ModelRot.SetRotation(CVector3::AxisY(), angle);
	//�O�������X�V
	ForwardUpdate();
}

void Boss::AnimationInit()
{
	//�A�j���[�V�����f�[�^��ǂ݂���
	LoadAnimation(m_AnimationClip[State::Walk], L"BossWalk.tka");
	m_AnimationClip[State::Walk].SetLoopFlag(true);
	LoadAnimation(m_AnimationClip[State::Attack], L"BossAttack.tka");
	LoadAnimation(m_AnimationClip[State::AppearanceRoar], L"BossAppearanceRoar.tka");
	LoadAnimation(m_AnimationClip[State::NormalRoar], L"BossNormalRoar.tka");
	LoadAnimation(m_AnimationClip[State::Down], L"BossDown.tka");
	LoadAnimation(m_AnimationClip[State::Die], L"BossDie.tka");

	//�A�j���[�V������������
	InitAnimation(m_AnimationClip,State::StateNum);
	//�C�x���g���X�i�[��ݒ�
	m_Animation.AddAnimationEventListener([&](const wchar_t* ClipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}

void Boss::OnAnimEvent(const wchar_t * eventName)
{	
	//AttackStart�̖��O����������
	if (wcscmp(eventName, L"AttackStart") == 0) {
		//�U����������
		AIAttack(Damage, Eria);
	}
	//AttackEnd�̖��O����������
	if (wcscmp(eventName, L"AttackEnd") == 0) {
		//�U�����������
		DeleteGO(m_HaveAttack);
		m_HaveAttack = nullptr;
	}
	if (wcscmp(eventName, L"RoorSound") == 0) {
		m_RoarSound.Play();
	}
}

void Boss::RoarUpdate()
{
	m_RoarTime += gameTime().GetFrameDeltaTime();
}

void Boss::InitSprite()
{
	m_BossSprite = NewGO< BossHpSprite>(0);
	m_BossSprite->SetHp(m_MaxHp);
}
