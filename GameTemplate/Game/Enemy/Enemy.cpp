#include "pch.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "Enemy/State/EnemyAttackState.h"
#include "Enemy/State/EnemyIdleState.h"
#include "Enemy/State/EnemyWalkState.h"
#include "Enemy/State/IEnemyState.h"
#include "Enemy/State/EnemyDamageState.h"
#include "State/EnemyDown.h"
#include "EnemyAttack.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::OnDestroy()
{
	//���̓G�Ɋ֌W����C���X�^���X���폜
	DeleteGO(m_Skin);
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HpUnderSprite);
}

void Enemy::Move(CVector3 move)
{
	//��]�̍X�V
	EnemyRot();
	//�����蔻������s
	m_Pos = m_CharaCon.Execute(gameTime().GetFrameDeltaTime(), move);
	//���f���̈ʒu��ݒ�
	m_Skin->SetPosition(m_Pos);
	//���f���̉�]��ݒ�
	m_Skin->SetRotation(m_Rot);
	//�U���̌�����r�܂ł̋���
	const float AttackReach = 100.0f;
	m_AttackPos = m_Pos + m_forward * AttackReach;
}
void Enemy::EnemyRot()
{
	//�v���C���[�Ƃ̋����𑪂�
	CVector3 diff = m_Player->GetPosition() - m_Pos;
	//�����̕������g���ĉ�]�ʂ����߂�
	float angle = atan2(diff.x, diff.z);
	//��]�ʂ�ۑ�
	m_Rot.SetRotation(CVector3::AxisY(), angle);
	//�O�������X�V
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rot);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_forward.Normalize();
}

void Enemy::HitDamege(const float damege) {
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
	//�v���C���[�̃|�C���^��������
	m_Player = FindGO<Player>("player");
	//�����ʒu��ݒ�
	m_Pos = m_SpownPosition;

	//���f����������
	SkinModelInit();

	//�L�����R����������
	CharaConInit();

	//HP�̃X�v���C�g��������
	HpSpriteInit();

	//�A�j���[�V������������
	AnimetionInit();

	//��������IdleState��ݒ�
	m_ActiveState = new EnemyIdleState(this);

	return true;
}

void Enemy::SkinModelInit()
{
	//���f����New
	m_Skin = NewGO<SkinModelRender>(0, "EnemySkin");
	//���f�������[�h
	m_Skin->Init(L"Assets/modelData/keleton.cmo");
	//�ʒu��ݒ�
	m_Skin->SetPosition(m_Pos);
	//��]��ݒ�
	m_Skin->SetRotation(m_Rot);
	//�傫����ݒ�
	m_Skin->SetScale(m_Scale);
	//�����_�[���[�h��ݒ�
	m_Skin->SetRenderMode(1);
}

void Enemy::CharaConInit()
{
	//�L�����R����ݒ�
	const float radius = 20.0f;
	m_CharaCon.Init(radius, m_height, m_Pos);
}

void Enemy::HpSpriteInit()
{
	//hp�X�v���C�g��ݒ�
	const float hpSpriteSizeY = 10.0f;
	m_HpPosition = m_Pos;
	//�X�v���C�g�̃T�C�Y��ݒ�
	CVector3 SpriteSize = CVector3::One();
	float sizeX = m_SpriteSize * m_Hp;
	SpriteSize.x = sizeX;
	//TopSprite��������
	HpTopSpriteInit(hpSpriteSizeY, SpriteSize);
	//UnderSprite��������
	HpUnderSprite(hpSpriteSizeY, SpriteSize);
}


void Enemy::HpTopSpriteInit(const float SizeY, const CVector3& Scale)
{
	//Hp��New
	m_HpTopSprite = NewGO<SpriteRender>(2);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_Hp, SizeY, true);
	//�ʒu���X�V
	m_HpTopSprite->SetPosition(m_HpPosition);
	//�傫�����X�V
	m_HpTopSprite->SetScale(Scale);
	//��_���X�V
	m_HpTopSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//�J���������ɉ摜��������
	m_HpTopSprite->SetIsFaceCamera(true);
}

void Enemy::HpUnderSprite(const float SizeY, const CVector3& Scale)
{
	//Hp��New
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, SizeY, true);
	//�ʒu���X�V
	m_HpUnderSprite->SetPosition(m_HpPosition);
	//�傫�����X�V
	m_HpUnderSprite->SetScale(Scale);
	//��_���X�V
	m_HpUnderSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//�J���������ɉ摜��������
	m_HpUnderSprite->SetIsFaceCamera(true);
}

void Enemy::AnimetionInit()
{
	//�A�j���[�V���������[�h
	m_AniClip[State::Walk].Load(L"Assets/AnimData/SkeltonWalk.tka");
	//���[�v�t���O��L��
	m_AniClip[State::Walk].SetLoopFlag(true);
	m_AniClip[State::Attack].Load(L"Assets/AnimData/SkeltonAttack.tka");
	m_AniClip[State::Damege].Load(L"Assets/AnimData/SkeltonDamage.tka");
	m_AniClip[State::Down].Load(L"Assets/AnimData/SkeltonDown.tka");
	m_AniClip[State::Idle].Load(L"Assets/AnimData/SkeltonIdle.tka");

	//���[�v�t���O��L��
	m_AniClip[State::Idle].SetLoopFlag(true);
	//�A�j���[�V������ݒ�
	m_Animation.Init(m_Skin->GetModel(), m_AniClip, State::Num);
	//�C�x���g���X�i�[��ݒ�
	m_Animation.AddAnimationEventListener([&](const wchar_t* ClipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}

void Enemy::OnAnimEvent(const wchar_t* eventName)
{
	//AttackStart�̖��O����������
	if (wcscmp(eventName, L"AttackStart") == 0) {
		//�U�������New
		attack = NewGO<EnemyAttack>(0, "enemyAttack");
		//�U����
		const float AttackDamage = 10.0f;
		//�U���͈�
		const float AttackEria = 135.0f;
		//�U����ݒ�
		attack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	//AttackEnd�̖��O����������
	if (wcscmp(eventName, L"AttackEnd") == 0) {
		//�U�����������
		DeleteGO("enemyAttack");
	}
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
		//CreateEnemyAttack();
		break;
	case State::Damege:		//�U�����������
		delete m_ActiveState;
		DeleteGOs("enemyAttack");
		m_ActiveState = new EnemyDamageState(this);
		break;
	case State::Down:		//����
		delete m_ActiveState;
		DeleteGOs("enemyAttack");
		m_CharaCon.RemoveRigidBoby();
		m_HpUnderSprite->SetAlpha(0.0f);
		m_ActiveState = new EnemyDown(this);
	}
	m_State = st;
}

void Enemy::Update()
{
	//�X�v���C�g���X�V
	UpdateSprite();
	//�X�e�[�g���X�V
	m_ActiveState->Update();
	//�X�e�[�g��ύX����
	ChangeState(m_NextState);
	//�A�j���[�V�������X�V
	m_Animation.Update(gameTime().GetFrameDeltaTime());
}

void Enemy::UpdateSprite()
{
	//Hp�̈ʒu��G�̈ʒu�ɍ��킹��
	m_HpPosition = m_Pos;
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

void Enemy::HpPosAdjustment()
{
	//HP��������Ə�ɒu��
	const float HpPosUp = 10.0f;
	m_HpPosition.y += m_height + HpPosUp;
	//��_�����炵�Ă���̂�
	//���̃Y�����C��
	CVector3 AddSpritePos = g_camera3D.GetRight()*-50.0f;
	m_HpPosition -= AddSpritePos;
}

bool Enemy::IsWalk() const
{
	//�v���C���[�Ƃ̋����𔻒�
	CVector3 Diff = m_Player->GetPosition() - m_Pos;
	//���E
	const float visility = 500.0f;
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
	CVector3 Diff = m_Player->GetPosition() - m_Pos;
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