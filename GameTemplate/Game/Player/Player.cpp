#include "Player.h"
#include "State/PlayerStateIdle.h"
#include "State/PlayerStateRun.h"
#include "State/PlayerStateAttack.h"
#include "State/PlayerStateBackStep.h"
#include "State/PlayerStateRollingAttack.h"
#include "State/PlayerStateDamage.h"
#include "PlayerAttack.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	m_Model = NewGO<SkinModelRender>(0);
	//cmo�t�@�C���̓ǂݍ��݁B
	m_Model->Init(L"Assets/modelData/Player.cmo");
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Model->SetRenderMode(enSilhouetteDraw);
	//m_CharaCon.Init(20.0f, 80.0f, m_Pos);
	//�ҋ@�X�e�[�g���쐬����B
	m_currentState = new PlayerStateIdle(this);

	m_AnimeClip[idle].Load(L"Assets/animData/idol.tka");
	m_AnimeClip[idle].SetLoopFlag(true);

	m_AnimeClip[walk].Load(L"Assets/animData/walk.tka");
	m_AnimeClip[walk].SetLoopFlag(true);

	m_AnimeClip[Back].Load(L"Assets/animData/back.tka");

	m_AnimeClip[Attack].Load(L"Assets/animData/Attack.tka"); 
	m_AnimeClip[Attack].SetLoopFlag(false);

	m_AnimeClip[RollingAttack].Load(L"Assets/animData/RollingAttack.tka");

	m_Animation.Init(m_Model->GetModel(), m_AnimeClip, AnimeNum);

	m_Animation.Play(idle, 0.2f);
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {

		OnAnimEvent(eventName);
	});

	m_HpTopSprite = NewGO<SpriteRender>(2);
	m_HpTopSprite->Init(L"Assets/sprite/HP_Top_Red.dds", m_Hp, 10.0f,true);
	m_HpPosition = m_Pos;
	m_HpPosition.y += m_height + (m_radius * 2) + 20.0f;
	m_HpTopSprite->SetPosition(m_HpPosition);
	m_HpTopSprite->SetPivot({ 0.0f,0.0f });
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	m_HpUnderSprite->Init(L"Assets/sprite/HP_Under_Brack.dds", m_Hp, 10.0f,true);
	m_HpUnderSprite->SetPosition(m_HpPosition);
	return true;
}
void Player::OnAnimEvent(const wchar_t* eventName)
{
	if (wcscmp(eventName, L"AttackEnd1") == 0) {
		if (m_ComboAttack) {
			PlayerAttack* PlAttack = NewGO< PlayerAttack>(0);
			PlAttack->Init(20.0f, 20.0f, m_AttackPos, m_AttackFrame);
			m_AttackFrame = 0;
			m_ComboAttack = false;
		}
		else {
			SetIdleState();
		}
	}
	if (wcscmp(eventName, L"AttackEnd2") == 0) {
		if (!m_ComboAttack) {
			PlayerAttack* PlAttack = NewGO< PlayerAttack>(0);
			PlAttack->Init(50.0f, 40.0f, m_AttackPos, m_AttackFrame);
			m_AttackFrame = 0;
			SetIdleState();
		}
		m_ComboAttack = false;
	}
}
void Player::UpdateSprite()
{
	m_HpPosition = m_Pos;
	m_HpPosition.y += m_height + (m_radius * 2) + 20.0f;
	//m_HpPosition.x -= 100.0f;
	//Hp���v���C���[�̐^�񒆂ɒu��
	float sizeX = m_SpriteSize * m_Hp;
	m_HpPosition.x -= 60.0f;
	m_HpTopSprite->SetPosition(m_HpPosition);
	m_HpUnderSprite->SetPivot({ 0.0f,0.0f });
	m_HpUnderSprite->SetPosition(m_HpPosition);
	m_HpTopSprite->SetPivot({ 0.0f,0.0f });
	m_HpTopSprite->SetScale({ 2.0,1.0f,1.0f });
}
void Player::CreateAttack()
{
	PlayerAttack* PlAttack = NewGO<PlayerAttack>(0);
	PlAttack->Init(10.0f,100.0f, m_AttackPos, 60.0f);
	m_AttackFrame = 0;

}
void Player::Update()
{
	m_AttackFrame++;
	if (m_state == State::State_Attack) {
		if (g_pad[0].IsTrigger(enButtonX)) {
			m_ComboAttack = true;
		}
	}
	UpdateState();
	m_MoveSpeed = m_Animation.Update(1.0f / 60.0f * m_mulAnimSpeed);
	//3dsMax�̋�Ԃ���Q�[����ԂɈړ����x��ύX�B
	float tmp = m_MoveSpeed.y;
	m_MoveSpeed.y = m_MoveSpeed.z;
	m_MoveSpeed.z = -tmp;

	//���f����Ԃ��烏�[���h��Ԃɕϊ��B
	m_Rot.Multiply(m_MoveSpeed);

	UpdateSprite();

	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Model->GetModel());
	PlayerMove();
	PlayerRotate();
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rot);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_forward.Normalize();
	m_AttackPos = m_Pos + m_forward *100.0f;
}
void Player::PlayerRotate()
{
	if (m_currentState->IsPossibleRotate()) {
		CVector3 MoveSpeed = g_camera3D.GetForward()*g_pad[0].GetLStickYF();
		MoveSpeed -= g_camera3D.GetRight()*g_pad[0].GetLStickXF();
		//�����Ԃ̂Ƃ��̂݁B
		m_Rot.SetRotation(CVector3::AxisY(), atan2(MoveSpeed.x, MoveSpeed.z));
	}
}
void Player::PlayerMove()
{
	if (m_currentState->IsPossibleMove()) {
		//�v���C���[�̈ړ��ʂ̓A�j���[�V�����̍Đ�������������Ă���B
		m_Pos += m_MoveSpeed;
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
	case State_Backstep:	//�o�b�N�X�e�b�v���B
		delete m_currentState;
		m_currentState = new PlayerStateBackStep(this);
		break;
	case State_Attack:
		delete m_currentState;
		m_currentState = new PlayerStateAttack(this);
		CreateAttack();
		break;
	case State_RollingAttack:
		delete m_currentState;
		m_currentState = new PlayerStateRollingAttack(this);
		break;
	case State::State_Damage:
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


