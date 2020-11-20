#include "Player.h"
#include "State/PlayerStateIdle.h"

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
	m_Model->Init(L"Assets/modelData/PlayerArmor.cmo");
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	//m_CharaCon.Init(20.0f, 80.0f, m_Pos);

	//�ҋ@�X�e�[�g���쐬����B
	m_currentState = new PlayerStateIdle(this);

	m_AnimeClip[AnimePattern::idol].Load(L"Assets/animData/idol.tka");
	m_AnimeClip[AnimePattern::idol].SetLoopFlag(true);

	m_AnimeClip[AnimePattern::walk].Load(L"Assets/animData/walk.tka");
	m_AnimeClip[AnimePattern::walk].SetLoopFlag(true);
	
	m_AnimeClip[Back].Load(L"Assets/animData/back.tka");

	m_AnimeClip[AnimePattern::Attack].Load(L"Assets/animData/Attack.tka");

	m_AnimeClip[AnimePattern::RollingAttack].Load(L"Assets/animData/RollingAttack.tka");

	m_Animation.Init(m_Model->GetModel(), m_AnimeClip, AnimePattern::AnimeNum);

//	m_Model->SetRenderMode(RenderMode::Silhouette);
	return true;
}

void Player::Update()
{
	UpdateState();
	m_MoveSpeed = m_Animation.Update(1.0f / 60.0f * m_mulAnimSpeed);
	//3dsMax�̋�Ԃ���Q�[����ԂɈړ����x��ύX�B
	float tmp = m_MoveSpeed.y;
	m_MoveSpeed.y = m_MoveSpeed.z;
	m_MoveSpeed.z = -tmp;
	//���f����Ԃ��烏�[���h��Ԃɕϊ��B
	m_Rot.Multiply(m_MoveSpeed);
	
	PlayerMove();
	PlayerRotate();
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
}
void Player::PlayerRotate()
{
	if (m_currentState->IsPossibleRotate()) {
		//�����Ԃ̂Ƃ��̂݁B
		m_Rot.SetRotation(CVector3::AxisY(), atan2(-g_pad[0].GetLStickXF(), -g_pad[0].GetLStickYF()));
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
	return g_pad[0].IsPress(enButtonY);
}

bool Player::IsAttack() {
	return g_pad[0].IsPress(enButtonX);
}
void Player::ChangeState(State state)
{
	//�����œn���ꂽ�X�e�[�g�̃C���X�^���X���쐬�B
	switch (state) {
	case State_Idle:
		m_currentState = new PlayerStateIdle(this);
		break;
	case State_Run:		//���蒆

		break;
	case State_Backstep:	//�o�b�N�X�e�b�v���B

		break;
	case State_Attack:

		break;
	case State_RollingAttack:

		break;
	}

	m_state = state;

}
void Player::UpdateState()
{
	m_currentState->Update();
	//�e��Ԃ��Ƃ̏���
/*	switch (m_state) {
	case State_Idle:
		m_mulAnimSpeed = 1.0f;
		//�ҋ@��Ԃ̏���
		m_Animation.Play(idol, 0.2f);
		if (IsMove()) {
			m_state = State_Run;
		}
		if (IsBackStep()) {
			m_state = State_Backstep;
		}
		if (IsAttack()) {
			m_state = State_Attack;
		}
		if (IsRollingAttack()) {
			m_state = State_RollingAttack;
		}
		break;
	case State_Run:
		m_mulAnimSpeed = 1.0f;
		m_Animation.Play(walk, 0.2f);
		if (!IsMove()) {
			//�R���g���[���[�̓��͂��I������B
			m_state = State_Idle;
		}
		if (IsBackStep()) {
			m_state = State_Backstep;
		}
		if (IsAttack()) {
			m_state = State_Attack;
		}
		if (IsRollingAttack()) {
			m_state = State_RollingAttack;
		}
		break;
	case State_Backstep:
		//�o�b�N�X�e�b�v���̓A�j���[�V�����̍Đ����x��2�{�ɁB
		m_mulAnimSpeed = 1.5f;
		m_Animation.Play(Back, 0.2f);
		if (m_Animation.IsPlaying() == false) {
			m_state = State_Idle;
		}
		break;
	case State_Attack:
		m_mulAnimSpeed = 1.0f;
		m_Animation.Play(AnimePattern::Attack, 0.2f);
		if (m_Animation.IsPlaying() == false) {
			m_state = State_Idle;
		}
	case State_RollingAttack:
		m_mulAnimSpeed = 1.0f;
		m_Animation.Play(AnimePattern::RollingAttack,0.2f);
		if (m_Animation.IsPlaying() == false) {
			m_state = State_Idle;
		}
	}*/
}


