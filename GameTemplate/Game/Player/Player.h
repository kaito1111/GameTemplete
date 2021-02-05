#pragma once
#include "character/CharacterController.h"

class IPlayerState;

class Player : public IGameObject
{
public:
	//�v���C���[�̃X�e�[�g
	enum State {
		State_Idle,		//�ҋ@��
		State_Run,		//���蒆
		State_Backstep,	//�o�b�N�X�e�b�v���B
		State_Attack,
		State_RollingAttack,
		State_Num
	};
	enum AnimePattern {
		idle,
		walk,
		Cloase,
		Back,
		Attack,
		RollingAttack,
		AnimeNum
	};
	Player();
	~Player();
	bool Start();
	void Update();

	CVector3 GetPosition() {
		return m_Pos;
	}

	CVector3 AttackPos() {
		return m_AttackPos;
	}
	/// <summary>
	/// ��Ԃ�؂�ւ���B
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(State state);

	void TryChangIdleState() {
		if (!IsMove()) {
			ChangeState(State_Idle);
		}
	}
	/// <summary>
	/// �ړ��X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeMoveState()
	{
		if (IsMove()) {
			ChangeState(State_Run);
		}
	}
	/// <summary>
	/// �o�b�N�X�e�b�v�X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeBackStepState()
	{
		if (IsBackStep()) {
			ChangeState(State_Backstep);
		}
	}
	/// <summary>
	/// �U���X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeAttackState()
	{
		if (IsAttack()) {
			ChangeState(State_Attack);
		}
	}
	/// <summary>
	/// ��]�U���X�e�[�g�ɐ؂�ւ��邱�Ƃ��o������؂�ւ���B
	/// </summary>
	void TryChangeRollingAttackState()
	{
		if (IsRollingAttack()) {
			ChangeState(State_RollingAttack);
		}
	}
	void PlayAnimation(AnimePattern anim)
	{
		//�ҋ@��Ԃ̏���
		m_Animation.Play(anim, 0.2f);
	}
	/// <summary>
	/// �A�j���[�V�����̍Đ����x�ɏ�Z�����l��ݒ�B
	/// </summary>
	/// <param name="mulSpeed"></param>
	void SetMulAnimSpeed(float mulSpeed) 
	{
		m_mulAnimSpeed = mulSpeed;
	}
	/// <summary>
	/// �v���C���[�̃A�j���[�V�����Đ����H
	/// </summary>
	/// <returns></returns>
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	void HitDamage(float damege) {
		m_Hp -= damege;
	}
private:
	/// <summary>
	/// ��Ԃ̍X�V�B
	/// </summary>
	void UpdateState();
	/// <summary>
	/// �ړ����邩����
	/// </summary>
	/// <returns>true���A���Ă�����ړ�����B</returns>
	bool IsMove() const;
	/// <summary>
	/// �o�b�N�X�e�b�v���s���H
	/// </summary>
	/// <returns></returns>
	bool IsBackStep() const;
	/// <summary>
	/// �ʏ�U������H
	/// </summary>
	/// <returns></returns>
	bool IsAttack();
	/// <summary>
	/// ��]�U������H
	/// </summary>
	/// <returns></returns>
	bool IsRollingAttack();
	/// <summary>
	/// �v���C���[�̈ړ�����
	/// </summary>
	void PlayerMove();
	/// <summary>
	/// �v���C���[�̐��񏈗��B
	/// </summary>
	void PlayerRotate();
	/// <summary>
	/// �A�j���[�V�����C�x���g�������������ɌĂ΂�鏈���B
	/// </summary>
	/// <param name="eventName"></param>
	void OnAnimEvent(const wchar_t* eventName);

	void UpdateSprite();
private:
	bool m_ComboAttack = false;
	

	IPlayerState* m_currentState = nullptr;		//���݂̃X�e�[�g�B
	State m_state = State_Idle;					//�v���C���[�̌��݂̏�ԁB
	SkinModelRender* m_Model = nullptr;			//�X�L�����f���B
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	CVector3 m_MoveSpeed = CVector3::Zero();
	CharacterController m_CharaCon;
	
	float m_mulAnimSpeed = 1.0f;	//�A�j���[�V�������x�ɏ�Z����
	CVector3 m_AttackPos = CVector3::Zero();
	Animation m_Animation;
	AnimationClip m_AnimeClip[AnimePattern::AnimeNum];

	SpriteRender* m_HpTopSprite = nullptr;
	CVector3 m_HpPosition = CVector3::Zero();
	float m_Hp = 62.5;
	float m_SpriteSize = 0.025f;

	SpriteRender* m_HpUnderSprite = nullptr;

	float m_radius = 30.0f;
	float m_height =  110.0f;
	bool m_isInvokeAttackColli = false;	//�U�����肪�������Ă���H
};

