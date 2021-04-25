#include "Player.h"
#include "State/PlayerStateIdle.h"
#include "State/PlayerStateRun.h"
#include "State/PlayerStateAttack.h"
#include "State/PlayerStateBackStep.h"
#include "State/PlayerStateRollingAttack.h"
#include "State/PlayerStateDamage.h"
#include "PlayerAttack.h"

namespace {
	const float HpPosUp = 40.0f;//Hp���v���C���[�̂�����Ə�ɑ���
	const float radius = 35.0f;//�L�����R���̉���
}
Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	m_ModelScale = { 0.8f,0.8f,0.8f };//�v���C���[�̑傫��
													//�ݒ�㏭������������
	m_ModelPos = m_SpownPosition;
	CharacterInit(L"Player.cmo", radius,m_height,m_ModelPos);
	//�ҋ@�X�e�[�g���쐬����B
	m_currentState = new PlayerStateIdle(this);

	AnimetionInit();

	const float InterpolateTime = 0.2f;
	m_Animation.Play(idle, InterpolateTime);
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {

		OnAnimEvent(eventName);
	});

	SpriteInit();

	m_HitModel = NewGO<SkinModelRender>(0);
	m_HitModel->Init(L"DebugShere.cmo");
	//z�̓��[���h��Ԃł̂��ɂ�����
	//y�͍l�����Ȃ�
	m_HitModel->SetScale({ radius, radius, 1.0f });
	return true;
}
void Player::OnAnimEvent(const wchar_t* eventName)
{
	if (wcscmp(eventName, L"AttackEnd1") == 0) {
		if (!m_ComboAttack) {
			SetIdleState();
		}
	}
	if (wcscmp(eventName, L"AttackEnd2") == 0) {
		if (!m_ComboAttack) {
			SetIdleState();
		}
		m_ComboAttack = false;
	}
	if (wcscmp(eventName, L"AttackJubgmentStart1") == 0) {
		PlayerAttack* PlAttack = NewGO<PlayerAttack>(0, "playerAttack");
		const float AttackDamage = 32.0f;
		const float AttackEria = 105.0f;
		PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd1") == 0) {
		DeleteGO("playerAttack");
	}
	if (wcscmp(eventName, L"AttackJubgmentStart2") == 0) {
		if (m_ComboAttack) {
			m_ComboAttack = false;
			PlayerAttack* PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
			const float AttackDamage = 32.0f;
			const float AttackEria = 90.0f;
			PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
		}
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd2") == 0) {
		DeleteGO("playerAttack");
	}
	if (wcscmp(eventName, L"AttackJubgmentStart3") == 0) {
		PlayerAttack* PlAttack = NewGO< PlayerAttack>(0, "playerAttack");
		const float AttackDamage = 100.0f;
		const float AttackEria = 135.0f;
		PlAttack->Init(AttackDamage, AttackEria, m_AttackPos);
	}
	if (wcscmp(eventName, L"AttackJubgmentEnd3") == 0) {
		DeleteGO("playerAttack");
	}
}

void Player::AnimetionInit()
{
	m_AnimeClip[idle].Load(L"Assets/animData/idol.tka");
	m_AnimeClip[idle].SetLoopFlag(true);

	m_AnimeClip[walk].Load(L"Assets/animData/walk.tka");
	m_AnimeClip[walk].SetLoopFlag(true);

	m_AnimeClip[Roling].Load(L"Assets/animData/Rolling.tka");

	m_AnimeClip[Attack].Load(L"Assets/animData/Attack.tka");
	m_AnimeClip[Attack].SetLoopFlag(false);

	m_AnimeClip[RollingAttack].Load(L"Assets/animData/RollingAttack.tka");

	m_AnimeClip[Damage].Load(L"Assets/animData/damage.tka");

	m_Animation.Init(m_Model->GetModel(), m_AnimeClip, AnimeNum);
}

void Player::SpriteInit()
{
	const float HpHeight = 10.0f;
	m_HpTopSprite = NewGO<SpriteRender>(2);
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_MaxHp, HpHeight, true);
	m_HpPosition = m_ModelPos;
	m_HpPosition.y += m_height + HpPosUp;
	m_HpTopSprite->SetPosition(m_HpPosition);
	m_HpTopSprite->SetPivot({ SpriteRender::XCenter(),SpriteRender::Up() });
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_MaxHp, HpHeight, true);
	m_HpUnderSprite->SetPosition(m_HpPosition);
	float sizeX = m_SpriteSize * m_MaxHp;
	CVector3 SpriteScale = CVector3::One();
	SpriteScale.x = sizeX;
	m_HpUnderSprite->SetScale(SpriteScale);
	m_HpTopSprite->SetScale(SpriteScale);
	m_HpUnderSprite->SetIsFaceCamera(true);
	m_HpTopSprite->SetIsFaceCamera(true);
}
void Player::UpdateSprite()
{
	m_HpPosition = m_ModelPos;
	m_HpPosition.y += m_height + HpPosUp;
	//m_HpPosition.x -= 100.0f;
	//Hp���v���C���[�̐^�񒆂ɒu��
	CVector3 AddSpritePos = g_camera3D.GetRight()*50.0f;
	m_HpPosition += AddSpritePos;
	m_HpTopSprite->SetPosition(m_HpPosition);
	m_HpUnderSprite->SetPivot({SpriteRender::Left(),SpriteRender::Up() });
	m_HpUnderSprite->SetPosition(m_HpPosition);
	m_HpTopSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	CVector3 SpriteSize = CVector3::One();
	float sizeX = m_SpriteSize * m_Hp;
	SpriteSize.x = sizeX;
	m_HpTopSprite->SetScale(SpriteSize);
}
void Player::Update()
{
	m_mutekiflame--;
	if (m_state == State::State_Attack) {
		if (g_pad[0].IsTrigger(enButtonX)) {
			m_ComboAttack = true;
		}
	}
	UpdateState();
	m_MoveSpeed = m_Animation.Update(gameTime().GetFrameDeltaTime() * m_mulAnimSpeed);
	//if (m_MoveSpeed.y < -10000.0f) {
	//	printf("hoge");
	//}
	//3dsMax�̋�Ԃ���Q�[����ԂɈړ����x��ύX�B
	float tmp = m_MoveSpeed.y;
	m_MoveSpeed.y = m_MoveSpeed.z;
	m_MoveSpeed.z = -tmp;

	//���f����Ԃ��烏�[���h��Ԃɕϊ��B
	m_ModelRot.Multiply(m_MoveSpeed);
	//HP�̃X�v���C�g���X�V
	UpdateSprite();
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Model->GetModel());
	//�ړ�����
	PlayerMove();
	//��]����
	Rotate();
	//���f���̍X�V
	CharacterModelUpdate();
	//�O�����̍X�V
	ForwardUpdate();
	const float AttackReach = 100.0f;
	m_AttackPos = m_ModelPos + m_forward * AttackReach;

	m_HitModel->SetPosition(m_ModelPos);
}
void Player::OnDestroy()
{
	DeleteGO(m_HpUnderSprite);
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HitModel);
}
void Player::Rotate()
{
	if (m_currentState->IsPossibleRotate()) {
		//�J�����̕����ɍ��킹�Č�������
		CVector3 MoveSpeed = g_camera3D.GetForward()*g_pad[0].GetLStickYF();
		MoveSpeed -= g_camera3D.GetRight()*g_pad[0].GetLStickXF();
		//�����Ԏ��B
		m_ModelRot.SetRotation(CVector3::AxisY(), atan2(MoveSpeed.x, MoveSpeed.z));
	}
}
void Player::PlayerMove()
{
	if (m_currentState->IsPossibleMove()) {
		//�v���C���[�̈ړ��ʂ̓A�j���[�V�����̍Đ�������������Ă���B
		if (m_MoveSpeed.Length() < 1.0f) {
			m_MoveSpeed = CVector3::Zero();
		}
		Move(m_MoveSpeed*60.0f);
	}
}
bool Player::IsMove() const
{
	//���X�e�B�b�N�̓��͂������true��Ԃ��B
	return fabsf(g_pad[0].GetLStickXF()) > 0.0f || fabsf(g_pad[0].GetLStickYF());
}
bool Player::IsBackStep() const
{
	//A�{�^���������ꂽ��o�b�N�X�e�b�v���s���B
	return g_pad[0].IsPress(enButtonA);

}

bool Player::IsRollingAttack() {
	return  g_pad[0].IsPress(enButtonY);
}

bool Player::IsAttack() {
	return g_pad[0].IsPress(enButtonX);
}
void Player::ChangeState(int state)
{
	//�����œn���ꂽ�X�e�[�g�̃C���X�^���X���쐬�B
	switch (state) {
	case State_Idle:
		if (m_currentState != nullptr) {
			delete m_currentState;
		}
		m_currentState = new PlayerStateIdle(this);
		break;
	case State_Run:		//���蒆
		delete m_currentState;
		m_currentState = new PlayerStateRun(this);
		break;
	case State_Roling:	//�o�b�N�X�e�b�v���B
		delete m_currentState;
		m_currentState = new PlayerStateBackStep(this);
		break;
	case State_Attack:
		delete m_currentState;
		m_currentState = new PlayerStateAttack(this);
		break;
	case State_RollingAttack:
		delete m_currentState;
		m_currentState = new PlayerStateRollingAttack(this);
		break;
	case State::State_Damage:
		DeleteGOs("playerAttack");
		delete m_currentState;
		m_currentState = new PlayerStateDamage(this);
		break;
	}

	m_state = state;
}

void Player::UpdateState()
{
	m_currentState->Update();
	if (m_state != m_NextState) {
		ChangeState(m_NextState);
	}
}