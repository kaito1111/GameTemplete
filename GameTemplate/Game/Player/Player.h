#pragma once
#include "character/CharacterController.h"

class IPlayerState;

class Player : public IGameObject
{
public:
	////��Ԃ̎�ނ�enum��
	enum State {
		State_Idle,		//�ҋ@��
		State_Run,		//���蒆
		State_Backstep,	//�o�b�N�X�e�b�v���B
		State_Attack,	//�U����
		State_RollingAttack,//���[�����O�A�^�b�N��
		State_Damage,	//�_���[�W��
		State_Num
	};
	//�A�j���[�V�����̐�
	//�X�e�[�g�Ɠ����ꏊ�ɂɂ��Ȃ��ƃo�O��܂�
	enum AnimePattern {
		idle,			//�ҋ@
		walk,			//����
		Back,			//�o�b�N�X�e�b�v
		Attack,			//�U��
		RollingAttack,	//���[�����O�A�^�b�N
		Damage,			//�_���[�W
		AnimeNum
	};
	Player();
	~Player();
	//������
	bool Start()override;
	//�X�V
	void Update()override;
	//�폜���ꂽ�u�ԂɌĂ΂��
	void OnDestroy()override;

	//�ʒu���擾
	CVector3 GetPosition() {
		return m_Pos;
	}
	//�U���ʒu���擾
	CVector3 AttackPos() {
		return m_AttackPos;
	}
	//hp���擾
	int GetHp() {
		return m_Hp;
	}
	/// <summary>
	/// �ҋ@�X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeIdleState() {
		if (!IsMove()) {
			m_NextState = State_Idle;
		}
	}
	/// /// <summary>
	/// �ړ��X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeMoveState()
	{
		if (IsMove()) {
			m_NextState = State_Run;
		}
	}
	/// <summary>
	/// �o�b�N�X�e�b�v�X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeBackStepState()
	{
		if (IsBackStep()) {
			m_NextState = State_Backstep;
		}
	}
	/// <summary>
	/// �U���X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeAttackState()
	{
		if (IsAttack()) {
			m_NextState = State_Attack;
		}
	}
	/// <summary>
	/// ��]�U���X�e�[�g�ɐ؂�ւ��邱�Ƃ��o������؂�ւ���B
	/// </summary>
	void TryChangeRollingAttackState()
	{
		if (IsRollingAttack()) {
			m_NextState = State_RollingAttack;
		}
	}
	//�ҋ@��Ԃ֑J��
	void SetIdleState() {
		m_NextState = State_Idle;
	}
	//�A�j���[�V�������Đ�
	void PlayAnimation()
	{
		//�ҋ@��Ԃ̏���
		m_Animation.Play(m_state, 0.2f);
	}
	/// <summary>
	/// �A�j���[�V�����̍Đ����x�ɏ�Z�����l��ݒ�B
	/// </summary>
	/// <param name="mulSpeed"></param>
	void SetMulAnimSpeed(const float mulSpeed) 
	{
		m_mulAnimSpeed = mulSpeed;
	}
	/// <summary>
	/// �v���C���[�̃A�j���[�V�����Đ����H
	/// </summary>
	/// <returns></returns>
	bool IsPlayAnimation() const {
		return m_Animation.IsPlaying();
	}
	//�_���[�W���󂯂�
	void HitDamage(const float damege) {
		//hp�����炷
		m_Hp -= damege;
		//�_���[�W��Ԃ֑J��
		m_NextState = State_Damage;
		//���G���Ԃ�ݒ�
		m_mutekiflame = 60;
	}
	//���G���Ԃ��擾
	int GetMutekiFlame() const {
		return m_mutekiflame;
	}

	//�����ʒu��ݒ�
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}
	//��]����ݒ�
	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}
	//Hp��ݒ�
	//�G���A�`�F���W�Ŏg��
	void SetSpwonHp(const int hp) {
		m_Hp = hp;
	}

	//�v���C���[�̍������擾
	float GetHeight() const {
		return m_height;
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

	//�X�v���C�g���X�V
	void UpdateSprite();

	/// <summary>
	/// ��Ԃ�؂�ւ���B
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(int state);
private:
	bool m_ComboAttack = false;
	

	IPlayerState* m_currentState = nullptr;		//���݂̃X�e�[�g�B
	int m_state = State_Idle;					//�v���C���[�̌��݂̏�ԁB
	int m_NextState = State::State_Idle;		//���̏�ԁB
	SkinModelRender* m_Model = nullptr;			//�X�L�����f���B
	CVector3 m_Pos = CVector3::Zero();			//�ʒu
	CQuaternion m_Rot = CQuaternion::Identity();//��]��
	CVector3 m_MoveSpeed = CVector3::Zero();	//�ړ���
	CharacterController m_CharaCon;				//�L�����R��
	
	float m_mulAnimSpeed = 1.0f;				//�A�j���[�V�������x�ɏ�Z����
	CVector3 m_AttackPos = CVector3::Zero();	//�U���ꏊ
	Animation m_Animation;						//�A�j���[�V����
	AnimationClip m_AnimeClip[AnimePattern::AnimeNum];//�A�j���[�V�����N���b�v

	SpriteRender* m_HpTopSprite = nullptr;		//��̊G
	CVector3 m_HpPosition = CVector3::Zero();	//�G�̈ʒu
	float m_Hp = 62.5;							//�̗�
	const float m_MaxHp = 62.5;					//�ő�̗�
	const float m_SpriteSize = 0.025f;			//hp�̊G�𒲐�����萔

	SpriteRender* m_HpUnderSprite = nullptr;	//���̊G

	const float m_radius = 35.0f;				//�L�����R���̉���
	const float m_height =  110.0f;				//�L�����R���̏c��
	bool m_isInvokeAttackColli = false;			//�U�����肪�������Ă���H

	CVector3 m_forward = CVector3::Front();		//�O����

	int m_mutekiflame = 0;						//���G����

	SkinModelRender* m_HitModel = nullptr;		//�f�o�b�O�p�̃��f��

	CVector3 m_SpownPosition = CVector3::Zero();//�����ʒu
};

