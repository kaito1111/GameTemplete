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
	//�X�v���C�g�̊�_�����炵�Ă���̂�
	//���̃Y�����C��
	const float spriteFix = -50.0f;
	const float HpPosUp = 30.0f;	//HP��������Ə�ɒu��
	const float HpSpriteDeadAlpha = 0.0f;//�{�X�����񂾂Ƃ���Hp�o�[�������Ȃ�����
	const float ModelAmbientColor = 0.2f;//���f���̊����̖��邳
	const float EffectScale = 4.0f;
}

bool Boss::Start() {
	//�L�����N�^�[�R���g���[���[�����������A�������[���h�ɓo�^
	CharacterInit(L"Boss.cmo", radius, height, m_ModelPos);
	//���f���̃|�W�V������ݒ�
	m_Model->SetPosition(m_ModelPos);

	//�A�j���[�V�����̏��������Ă�
	AnimationInit();

	//���f���̉�]�̍X�V���Ă�
	Rotate();
	//���f���̉�]��ݒ�
	m_Model->SetRotation(m_ModelRot);

	//�v���C���[��������
	m_player = FindGO<Player>("player");

#ifdef _DEBUG
	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"DebugShere.cmo");
	//z�̓��[���h��Ԃł̂��ɂ�����
	//y�͍l�����Ȃ�
	m_HitModel->SetScale({ radius, radius, 1.0f });
#endif
	//�U���͈�
	AttackReach = 150.0f;

	//HP���ő�HP�ɐݒ�
	m_Hp = BossMaxHp;

	//�X�v���C�g�̏������֐����Ă�
	InitSprite();

	//���K����ݒ�
	m_RoarSound.Init(L"RoarSound.wav");
	InitHpSprite(m_Hp, m_MaxHp);
	//Hp�X�v���C�g�̓����x
	//���̏��HP�X�v���C�g�͂����Č����Ȃ��̂�0�ɂ���
	m_HpTopSprite->SetAlpha(0.0f);
	m_HpUnderSprite->SetAlpha(0.0f);
	m_HpTopTranslucentSprite->SetAlpha(0.0f);

	//���f���̊�����ݒ肷��
	m_Model->SetAmbientColor(ModelAmbientColor);
	return true;
}

void Boss::Update()
{
	if (m_NextState != m_CurrentState) {
		//��Ԃ�ύX
		ChengeState(m_NextState);
	}
	//���݂̏�Ԃ��X�V
	m_ActiveState->Update();
	//Animation���v���C
	m_Animation.Play(m_CurrentState);
	//Boss�p�̃X�v���C�g��Hp��ݒ�
	m_BossSprite->SetHp(m_Hp);
	//Charactor�N���X��Hp�o�[�̍X�V
	SpriteUpdate();
	//�O�������X�V
	ForwardUpdate();
}

void Boss::OnDestroy()
{
#ifdef _DEBUG
	//�����蔻�肪�����郂�f���̍폜
	DeleteGO(m_HitModel);
#endif
	//�{�X��Hp�c�ʂ�\���Ă���X�v���C�g���폜
	DeleteGO(m_BossSprite);
	//Charactor�N���X��Destroy�֐����Ă�
	Destroy();
	//���݂̏�Ԃ�\���Ă���N���X��nullptr�łȂ��Ȃ�
	if (m_ActiveState != nullptr) {
		//���݂̏�Ԃ��X�V���Ă���N���X���폜
		delete m_ActiveState;
	}
}

void Boss::IsChengeAttackState()
{
	//�v���C���[�Ƌ����𑪂�
	CVector3 Diff = m_player->GetPosition() - m_ModelPos;
	//�����v���C���[���U���G���A���Ȃ�
	if (Diff.Length() < InPlayer) {
		//���̏�Ԃ͍U���ɂȂ�
		m_NextState = State::Attack;
	}
}

void Boss::IsChengeNormalRoar()
{
	//���K�����Ă��Ȃ����Ԃ𑪂�
	m_RoarTime += gameTime().GetFrameDeltaTime();
	//���K�����Ă��Ȃ����Ԃ��N�[���^�C���ȏ�Ȃ�
	if (m_RoarTime > m_CoolTimeRoar) {
		//���K�����̂�0�ɖ߂�
		m_RoarTime = 0;
		//���̏�Ԃ𕁒ʂ̙��K�ɂ���
		m_NextState = State::NormalRoar;
	}
}

void Boss::ChengeState(const State& state)
{
	//���̏�Ԃɂ���ď�����ς���
	switch (state) {
	case State::Walk:
		//���݂̏�Ԃ�Walk�ɕύX
		m_ActiveState = new BossWalkState(this);
		//�񋓌^�̏�Ԃ��ύX
		m_CurrentState = state;
		break;
	case State::Attack:
		//���݂̏�Ԃ�Attack�ɕύX
		m_ActiveState = new BossAttackState(this);
		//�񋓌^�̏�Ԃ��ύX
		m_CurrentState = state;
		break;
	case State::AppearanceRoar:
		//���݂̏�Ԃ�o�ꎞ�̙��K��ԂɕύX
		m_ActiveState = new BossAppearanceRoarState(this);
		//�񋓌^�̏�Ԃ��ύX
		m_CurrentState = state;
		break;
	case State::NormalRoar:
		//���݂̏�Ԃ�ʏ�̙��K��ԂɕύX
		m_ActiveState = new BossNormalRoar(this);
		//�U�����Ȃ�U�����������
		DeleteAttack();
		//�񋓌^�̏�Ԃ��ύX
		m_CurrentState = state;
		break;
	case State::Die:
		//�U�����Ȃ�U�����������
		DeleteAttack();
		//���݂̏�Ԃ����񂾏�ԂɕύX
		m_ActiveState = new BossDieState(this);
		//�񋓌^�̏�Ԃ��ύX
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
	//RoorSound�̖��O����������
	if (wcscmp(eventName, L"RoorSound") == 0) {
		//���K�̉����o��
		m_RoarSound.Play();
		//���K���̃G�t�F�N�g�𗬂�
		Effect* m_Effect = NewGO<Effect>(0);
		m_Effect->Play(L"Assets/effect/BossRoar.efk");
		CVector3 RoarPos = m_ModelPos;
		//�G�t�F�N�g�̍����̓��f���̔����̍����̈ʒu�ɂ���
		RoarPos.y += height / 2;
		//�G�t�F�N�g�̈ʒu��ݒ�
		m_Effect->SetPosition(RoarPos);
		//�G�t�F�N�g�̃X�P�[����ݒ�
		m_Effect->SetScale(CVector3::One()*EffectScale);
	}
}

void Boss::InitSprite()
{
	//�{�X�p��Hp�𓮓I�m�ۂ���
	m_BossSprite = NewGO< BossHpSprite>(0);
	//�{�X��Hp��ݒ肷��
	m_BossSprite->SetHp(m_MaxHp);
}
