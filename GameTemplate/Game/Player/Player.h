#pragma once
#include "character/CharacterController.h"
#include "GameSceneFunction/Anime.h"
class IPlayerState;
class HuntedSprite;
class IWeapon;
class PlayerAttack;

class Player final : public Anime
{
public:
	////��Ԃ̎�ނ�enum��
	enum State {
		Title,		//�^�C�g���̑ҋ@���i�����Ă���j
		Stand,		//������
		TakeOut,	//������o����
		TitleWalk,  //TitlePos�Ɍ������ĕ���
		Idle,		//�ҋ@��
		Walk,		//���蒆
		Roling,	//���[�����O���B
		Attack,	//�U����
		RollingAttack,//���[�����O�A�^�b�N��
		Damage,	//�_���[�W��
		Die,    //���S
		GameClear,
		Num
	};
	Player();
	~Player();
	//������
	bool Start()override final;
	//�X�V
	void Update()override final;
	//�폜���ꂽ�u�ԂɌĂ΂��
	void OnDestroy()override final;

	//�ʒu���擾
	CVector3 GetPosition() {
		return m_ModelPos;
	}
	//�U���ʒu���擾
	CVector3 AttackPos() {
		return m_AttackPos;
	}
	//hp���擾
	float GetHp() const{
		return m_Hp;
	}
	/// <summary>
	/// �ҋ@�X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeIdleState() {
		if (!IsMove()) {
			m_NextState = State::Idle;
		}
	}
	/// /// <summary>
	/// �ړ��X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeMoveState()
	{
		if (IsMove()) {
			m_NextState = State::Walk;
		}
	}
	/// <summary>
	/// �o�b�N�X�e�b�v�X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeBackStepState()
	{
		if (IsBackStep()) {
			m_NextState = State::Roling;
		}
	}
	/// <summary>
	/// �U���X�e�[�g�ɐ؂�ւ��邱�Ƃ��ł�����؂�ւ���B
	/// </summary>
	void TryChangeAttackState()
	{
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}
	/// <summary>
	/// ��]�U���X�e�[�g�ɐ؂�ւ��邱�Ƃ��o������؂�ւ���B
	/// </summary>
	void TryChangeRollingAttackState()
	{
		if (IsRollingAttack()) {
			m_NextState = State::RollingAttack;
		}
	}
	//�^�C�g����Ԃ֑J��
	void SetTitleState() {
		m_NextState = State::Title;
	}
	void SetStandingState() {
		m_NextState = State::Stand;
	}
	void SetTakeOutState() {
		m_NextState = State::TakeOut;
	}
	void SetTitleWalk() {
		m_NextState = State::TitleWalk;
	}
	//�ҋ@��Ԃ֑J��
	void SetIdleState() {
		m_NextState = State::Idle;
	}
	void SetClearState() {
		m_NextState = State::GameClear;
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
	void HitDamage(const float damege) override{

		//hp�����炷
		m_Hp -= damege;
		//�_���[�W��Ԃ֑J��
		m_NextState = State::Damage;
		//Hp��0�ȉ��ɂȂ����玀��
		if (m_Hp <= 0.0f) {
			m_NextState = State::Die;
			m_Hp = 0;
		}
	}

	//�����ʒu��ݒ�
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}
	//��]����ݒ�
	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}
	//Hp��ݒ�
	//�G���A�`�F���W�Ŏg��
	void SetSpwonHp(const float hp) {
		m_Hp = hp;
	}

	//�v���C���[�̍������擾
	float GetHeight() const {
		return m_height;
	}

	//�v���C���[�̏�Ԃ��擾
	int GetState()const {
		return m_state;
	}
	void SetTitlePos(const CVector3& pos) {
		m_TitlePos = pos;
	}
	CVector3 GetTitlePos() {
		return m_TitlePos;
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
	void Rotate();
	/// <summary>
	/// �A�j���[�V�����C�x���g�������������ɌĂ΂�鏈���B
	/// </summary>
	/// <param name="eventName"></param>
	void OnAnimEvent(const wchar_t* eventName);

	/// <summary>
	/// ��Ԃ�؂�ւ���B
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(int state);

	//�A�j���[�V�����̏�����
	void AnimetionInit();

private:
	bool m_ComboAttack = false;
	

	IPlayerState* m_currentState = nullptr;		//���݂̃X�e�[�g�B
	int m_state = State::Idle;					//�v���C���[�̌��݂̏�ԁB
	int m_NextState = State::Idle;				//���̏�ԁB
	CVector3 m_MoveSpeed = CVector3::Zero();	//�ړ���
	
	float m_mulAnimSpeed = 1.0f;				//�A�j���[�V�������x�ɏ�Z����
	CVector3 m_AttackPos = CVector3::Zero();	//�U���ꏊ
	AnimationClip m_AnimeClip[State::Num];		//�A�j���[�V�����N���b�v

	const float m_SpriteSize = 0.025f;			//hp�̊G�𒲐�����萔

	const float m_height =  110.0f;				//�L�����R���̏c��
	bool m_isInvokeAttackColli = false;			//�U�����肪�������Ă���H

#ifdef _DEBUG
	SkinModelRender* m_HitModel = nullptr;		//�f�o�b�O�p�̃��f��
#endif
	CVector3 m_SpownPosition = CVector3::Zero();//�����ʒu
	HuntedSprite* m_HuntedSprite = nullptr;
	SoundSource m_WalkSound;
	SoundSource m_WalkSound2;
	SoundSource m_SwingSound;

	IWeapon* m_weapon = nullptr;
	CVector3 m_TitlePos = CVector3::Zero();
	PlayerAttack* m_PlAttack = nullptr;
	PointLight* m_myLuminous = nullptr;			//���������点��|�C���g���C�g�@���O�͓K��
};

