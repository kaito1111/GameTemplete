#pragma once
#include "character/CharacterController.h"
#include "GameSceneFunction/Anime.h"
class IPlayerState;
class HuntedSprite;
class IWeapon;
class PlayerAttack;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player final : public Anime
{
public:
	//�v���C���[�̃X�^�~�i����ʂ�\�����񋓌^
	enum  StaminaCostList {
		StaminaRun = 1,				//���蒆
		StaminaRolling = 30,		//���[�����O��
		StaminaAttack = 20,			//�U����
		StaminaRollingAttack = 60,	//���[�����O�U����
		StaminaNum					
	};
	//��Ԃ̎�ނ�\�����񋓌^
	enum State {
		Title,			//�^�C�g���̑ҋ@���i�����Ă���j
		Stand,			//����
		Idle,			//�ҋ@��
		Walk,			//���蒆
		Roling,			//���[�����O���B
		Attack,			//�U����
		RollingAttack,	//���[�����O�A�^�b�N��
		Damage,			//�_���[�W��
		Die,			//���S
		GameClear,		//�Q�[���N���A
		Num
	};
	/// <summary>
	/// �C���X�^���X�����������ƁA��x�����Ă΂��J�n����
	/// </summary>
	/// <remarks>
	/// Unity��Start()�֐��̎d�l�ɏ����B
	/// </remarks>
	/// <returns>
	/// true���A���Ă�����A�����������B
	/// �����t���[���ɂ킽���ď��������������ꍇ�́A
	/// �����������܂�false��Ԃ��B
	/// </returns>
	bool Start()override final;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override final;
	/// <summary>
	/// �C���X�^���X���j������鎞�ɌĂ΂��֐��B
	/// </summary>
	/// <remarks>
	/// �{�G���W���Ŏ������Ă���A�Q�[���I�u�W�F�N�g���폜����
	/// DeleteGO�֐��́A�����ɃC���X�^���X���폜����킯�ł͂Ȃ��A
	/// 1�t���[���x��ăC���X�^���X���폜�����B
	/// ���̂��߁A�f�X�g���N�^�̌Ăяo�����ADeleteGO�̌Ăяo������1�t���[���x��邱�ƂƂȂ�B
	/// DeleteGO���Ă΂ꂽ�^�C�~���O�ŁA�s�������I��������OnDestroy()�ɋL�q����B
	/// </remarks>
	void OnDestroy()override final;

	/// <summary>
	/// �v���C���[���f���̈ʒu���擾
	/// </summary>
	/// <returns>���f���̈ʒu</returns>
	CVector3 GetPosition() {
		return m_ModelPos;
	}
	/// <summary>
	/// �v���C���[�̍U���ʒu���擾
	/// </summary>
	/// <returns>�U���ʒu</returns>
	CVector3 AttackPos() {
		return m_AttackPos;
	}
	/// <summary>
	/// �v���C���[�̎c��Hp���擾
	/// </summary>
	/// <returns>Hp���擾</returns>
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
	/// <summary>
	/// �^�C�g����Ԃ֑J��
	/// </summary>
	void SetTitleState() {
		m_NextState = State::Title;
	}
	/// <summary>
	/// ����Ԃ֑J��
	/// </summary>
	void SetStandingState() {
		m_NextState = State::Stand;
	}
	/// <summary>
	/// �ҋ@��Ԃ֑J��
	/// </summary>
	void SetIdleState() {
		m_NextState = State::Idle;
	}
	/// <summary>
	/// �Q�[���N���A�X�e�[�g�֑J��
	/// </summary>
	void SetClearState() {
		m_NextState = State::GameClear;
	}
	/// <summary>
	/// �A�j���[�V�������Đ�
	/// </summary>
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
	/// <summary>
	/// �_���[�W���󂯂�
	/// </summary>
	/// <param name="damege">�_���[�W��</param>
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

	/// <summary>
	/// �����ʒu��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}
	/// <summary>
	/// ��]����ݒ�
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}
	/// <summary>
	/// Hp��ݒ�
	/// �G���A�`�F���W�Ŏg��
	/// </summary>
	/// <param name="hp"></param>
	void SetSpwonHp(const float hp) {
		m_Hp = hp;
	}

	/// <summary>
	/// �v���C���[�̐g�����擾
	/// </summary>
	/// <returns>�L�����R���̍���</returns>
	float GetHeight() const {
		return m_height;
	}

	/// <summary>
	/// �v���C���[�̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	int GetState()const {
		return m_state;
	}
	/// <summary>
	/// �v���C���[�̃X�^�~�i�c�ʂ��擾
	/// </summary>
	/// <returns>�X�^�~�i�̎c��</returns>
	float GetStamina()const {
		return m_Stamina;
	}
	/// <summary>
	/// �X�^�~�i��ݒ肷��
	/// </summary>
	/// <param name="st"></param>
	void SetStamina(const float st) {
		m_Stamina = st;
	}
	/// <summary>
	/// �X�^�~�i�������Ƃ��ł��邩
	/// </summary>
	void IsStaminaRest() {
		m_StaminaRest = false;
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

	/// <summary>
	/// �A�j���[�V����������������
	/// </summary>
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
	HuntedSprite* m_HuntedSprite = nullptr;		//�Q�[���N���A���ɏo��X�v���C�g
	SoundSource m_WalkSound;					//������
	SoundSource m_WalkSound2;					//����������������ɗ����\������
	SoundSource m_SwingSound;					//�����U������

	IWeapon* m_weapon = nullptr;				//����̃X�L��
	PlayerAttack* m_PlAttack = nullptr;			//�v���C���[�̍U������
	PointLight* m_myLuminous = nullptr;			//���������点��|�C���g���C�g�@���O�͓K��
	SpriteRender* m_StaminaSprite = nullptr;	//�X�^�~�i�c�ʂ̃X�v���C�g
	float m_Stamina = 100.0f;					//�X�^�~�i�l
	SpriteRender* m_StaminaFrame = nullptr;		//�X�^�~�i�̃t���[��
	bool m_StaminaRest = true;					//�X�^�~�i���񕜂ł��邩
	float m_RestStopTime = 1.0f;				//�X�^�~�i���g���؂�Ɖ񕜏o���Ȃ��Ȃ�N�[���^�C��
	bool m_IsLastAttack = false;				//���̍U�����Ō�H
	float m_NewClearTime = 0.0f;				//Clear�X�v���C�g��New����^�C�~���O

	SoundSource m_RollingSound;					//��]���ɗ���鉹
};

