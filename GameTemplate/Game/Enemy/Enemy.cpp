#include "pch.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Enemy/State/EnemyAttackState.h"
#include "Enemy/State/EnemyIdleState.h"
#include "Enemy/State/EnemyWalkState.h"
#include "Enemy/State/IEnemyState.h"
#include "Enemy/State/EnemyDamageState.h"
#include "State/EnemyDown.h"
#include "GameSceneFunction/AIProcesing.h"
#include "GameSceneFunction/Attack.h"

namespace {
	const float visility = 500.0f;//���E	
	const float radius = 20.0f;//�L�����R���̕�
	const float m_height = 150.0f;				//�G�̐g��
	const float hpSpriteSizeY = 10.0f;	//�X�v���C�g�̏c��
	const float AttackDamage = 10.0f;	//�U����
	const float AttackEria = 135.0f;	//�U���͈�
	const float SpriteClear = 0.0f;	//�X�v���C�g�𓧖��ɂ���
	const float SpriteSize = 0.025f;			//hp�̃T�C�Y�𒲐�	
	const float EnemyMaxHp = 62.5;
	const float EnemyScale = 4.5f;
}

void Enemy::HitDamage(const float damege) {
	//����łȂ��Ȃ�Hp�����炷
	if (m_ActiveState->IsPossibleHpDown()) {
		m_Hp -= damege;
	}
	//Hp��0�ȏ�Ȃ�_���[�W���[�V������
	if (m_Hp > 0) {
		m_NextState = State::Damege;
	}
	//�ȉ��Ȃ�hp��0�ɂ��ĎE��
	else {
		m_Hp = 0;
		m_NextState = State::Down;
	}
}

bool Enemy::Start()
{
	//���f���̑傫���𒲐�
	m_ModelScale *= EnemyScale;
	//�v���C���[�̃|�C���^��������
	m_Player = FindGO<Player>("player");

	//���f���ƃL�����R����������
	CharacterInit(L"Skeleton.cmo", radius, m_height, m_ModelPos);

	m_Hp = EnemyMaxHp;
	//HP�̃X�v���C�g��������
	InitHpSprite(EnemyMaxHp,m_Hp);

	//�A�j���[�V������������
	AnimetionInit();

	//��������IdleState��ݒ�
	m_ActiveState = new EnemyIdleState(this);
	m_WalkSound.Init(L"EnemyWalk.wav");
	m_SwingSound.Init(L"EnemySwingSword.wav");
	//m_WalkSound.Play(true);
	//m_WalkSound.SetVolume(0.0f);
	m_Model->SetAmbientColor(0.4f);

	m_AttackVoice.Init(L"EnemyAttackVoice.wav"); 
	m_AttackVoice.SetVolume(3.0f);
	return true;
}
void Enemy::OnDestroy()
{
	Destroy();
	if (m_ActiveState != nullptr) {
		delete m_ActiveState;
	}
}
void Enemy::AnimetionInit()
{
	//�A�j���[�V���������[�h
	LoadAnimation(m_AniClip[State::Walk], L"SkeltonWalk.tka");
	//���[�v�t���O��L��
	m_AniClip[State::Walk].SetLoopFlag(true);
	LoadAnimation(m_AniClip[State::Attack],L"SkeltonAttack.tka");
	LoadAnimation(m_AniClip[State::Damege],L"SkeltonDamage.tka");
	LoadAnimation(m_AniClip[State::Down], L"SkeltonDown.tka");
	LoadAnimation(m_AniClip[State::Idle], L"SkeltonIdle.tka");
	//���[�v�t���O��L��
	m_AniClip[State::Idle].SetLoopFlag(true);
	//�A�j���[�V������ݒ�
	InitAnimation(m_AniClip, State::Num);
	//�C�x���g���X�i�[��ݒ�
	m_Animation.AddAnimationEventListener([&](const wchar_t* ClipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}

void Enemy::OnAnimEvent(const wchar_t* eventName)
{
	//AttackStart�̖��O����������
	if (wcscmp(eventName, L"AttackStart") == 0) {
		//�U����������
		AIAttack(AttackDamage, AttackEria, "enemyAttack");
	}
	//AttackEnd�̖��O����������
	if (wcscmp(eventName, L"AttackEnd") == 0) {
		//�U�����������
		DeleteAttack();
	}
	if (wcscmp(eventName, L"WalkSound1") == 0) {
		m_WalkSound.Play();
	}
	if (wcscmp(eventName, L"WalkSound2") == 0) {
		m_WalkSound.Play();
	}
	if (wcscmp(eventName, L"AttackVoice") == 0) {
		m_AttackVoice.Play();
	}
	//if (wcscmp(eventName, L"SwingSound") == 0) {
	//	m_WalkSound.Play();
	//}
}

void Enemy::ChangeState(int st)
{
	//�����œn���ꂽ�X�e�[�g�̃C���X�^���X���쐬�B
	switch (st) {
	case State::Idle:		//�ҋ@��
		if (m_ActiveState != nullptr) {
			delete m_ActiveState;
		}
		m_ActiveState = new EnemyIdleState(this);
		break;
	case State::Walk:		//���蒆
		delete m_ActiveState;
		m_ActiveState = new EnemyWalkState(this);
		break;
	case State::Attack:		//�U����
		delete m_ActiveState;
		m_ActiveState = new EnemyAttackState(this);
		break;
	case State::Damege:		//�U�����������
		delete m_ActiveState;
		DeleteAttack();
		m_ActiveState = new EnemyDamageState(this);
		break;
	case State::Down:		//����
		delete m_ActiveState;
		DeleteAttack();
		m_CharaCon.RemoveRigidBoby();
		m_HpUnderSprite->SetAlpha(SpriteClear);
		m_ActiveState = new EnemyDown(this);
	}
	m_State = st;
}

void Enemy::Update()
{
	//�X�v���C�g���X�V
	SpriteUpdate();
	//�X�e�[�g���X�V
	m_ActiveState->Update();
	//�X�e�[�g��ύX����
	ChangeState(m_NextState);
	//�O�����̍X�V
	ForwardUpdate();
	//�A�j���[�V�������X�V
	m_Animation.Update(gameTime().GetFrameDeltaTime());
	//���f�����ړ�
	CharacterModelUpdate();
	//hp�������邩�ǂ���
	UpdateHpAlpha();
}

bool Enemy::IsWalk() const
{
	//�v���C���[�Ƃ̋����𔻒�
	CVector3 Diff = m_Player->GetPosition() - m_ModelPos;
	//�����v���C���[�����E���Ȃ�
	if (Diff.Length() < visility) {
		Diff.Normalize();
		//�v���C���[���ڂ̑O���牽�x����Ă��邩����
		float ViewAngle = m_forward.Dot(Diff);
		//�G�̎���p
		const float fieldView = 0.7f;
		//������ɓ�����
		if (ViewAngle > fieldView) {
			return true;
		}
	}
	return false;
}
bool Enemy::IsAttack() const
{
	//�v���C���[�Ƃ̋������r
	CVector3 Diff = m_Player->GetPosition() - m_ModelPos;
	//�U��������Ɣ��f����͈�
	//�U���͈̔͂ł͂Ȃ�
	const float AttackRenge = 100.0f;
	//�U���͈͂ɓ�����
	if (Diff.Length() < AttackRenge) {
		//�v���C���[����O�������牽������Ă��邩
		float ViewAngle = m_forward.Dot(Diff);
		//����p
		const float fieldView = 0.7f;
		//���E���ɓ�����
		if (ViewAngle > fieldView) {
			return true;
		}
	}
	//������Ȃ�����
	return false;
}

void Enemy::Rotate()
{
	//�����ʒu�Ƃ̋����𑪂�
	CVector3 diff = m_Player->GetPosition() - m_ModelPos;
	//�����̕������g���ĉ�]�ʂ����߂�
	float angle = atan2(diff.x, diff.z);
	//��]�ʂ�ۑ�
	m_ModelRot.SetRotation(CVector3::AxisY(), angle);
	//�O�������X�V
	ForwardUpdate();
}
