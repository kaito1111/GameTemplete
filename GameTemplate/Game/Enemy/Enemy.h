#pragma once
#include "character/CharacterController.h"
class IEnemyState;
#include "Player/Player.h"
#include "GameSceneFunction/AIProcesing.h"
/// <summary>
/// �X�P���g��
/// </summary>
class Enemy final :public AIProcesing
{
public:
	/// <summary>
	/// ��Ԃ�\���񋓌^
	/// </summary>
enum State {
	Attack,
	Idle,
	Walk,
	Damege,
	Down,
	Num
};
public:
	/// <summary>
	/// �A�j���[�V�������Đ�
	/// </summary>
	/// <param name="st">
	/// ���݂̏�Ԃ�����
	/// enum��State���g���ƕ֗��B����
	/// </param>
	void PlayAnimation(State st) {
		m_Animation.Play(st, 0.2f);
	}
	/// <summary>
	/// �A�j���[�V�������Đ����H
	/// </summary>
	/// <returns>true�Ȃ�Đ����Ă���</returns>
	bool IsPlayingAnimation() const{
		return m_Animation.IsPlaying();
	}

	/// <summary>
	/// �v���C���[���U�����邩����
	/// </summary>
	void TryChangeAttackState() {
		//true�ōU��
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	/// <summary>
	/// �v���C���[��ǂ������邩���ׂ�
	/// </summary>
	void TryChangeWalk() {
		//true�ŕ���
		if (IsWalk()) {
			if (!m_WalkSound.IsPlaying()) {
				m_WalkSound.Play();
			}
			m_NextState = State::Walk;
		}
	}

	/// <summary>
	/// IdelState�ɑJ�ڂ������Ƃ���p
	/// </summary>
	void SetIdleState() {
		m_NextState = State::Idle;
	}

	/// <summary>
	/// �v���C���[����̍U��������������Ă΂��
	/// </summary>
	/// <param name="damege">�_���[�W��</param>
	void HitDamage(const float damege)override;

	/// <summary>
	/// �v���C���[�����ɕ���
	/// </summary>
	void EnemyWalk() {
		AIWalk();
	}
private:
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
	bool Start()override;

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
	/// �A�j���[�V������������
	/// </summary>
	void AnimetionInit();
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;

	/// <summary>
	/// eventName����A�j���[�V�����C�x���g���g���^�C�~���O���t�b�N���ď���������
	/// </summary>
	/// <param name="eventName">max�œo�^�����C�x���g�̖��O</param>
	void OnAnimEvent(const wchar_t* eventName);
	
	/// <summary>
	/// ���s��Ԃֈڍs�ł��邩�H
	/// </summary>
	/// <returns>true�ŁA�ł���</returns>
	bool IsWalk()const;
	/// <summary>
	/// �U����Ԃֈڍs�ł��邩�H
	/// </summary>
	/// <returns>true�ŁA�ł���</returns>
	bool IsAttack()const;

	/// <summary>
	/// ���f���̉�]����
	/// </summary>
	void Rotate()override;

	/// <summary>
	/// ��Ԃ�ύX����֐�
	/// </summary>
	/// <param name="state">���̏��</param>
	void ChangeState(int st);

private:
	AnimationClip m_AniClip[Num];				//�A�j���[�V�����̎��

	int m_State = State::Idle;					//���݂̃X�e�[�g���L������
												//�X�e�[�g��؂�ւ���Ƃ��Ɏg�p����
	IEnemyState* m_ActiveState = nullptr;		//���݂̃X�e�[�g
	int m_NextState = State::Idle;				//���̃X�e�[�g

	CVector3 m_AttackPos = CVector3::Zero();	//�U���̏ꏊ

	Player* m_Player = nullptr;					//�v���C���[�|�C���^

	SoundSource m_WalkSound;					//�����Ƃ��ɂȂ鉹
	SoundSource m_SwingSound;					//����U��Ƃ��ɂȂ鉹
	SoundSource m_AttackVoice;					//�U�����ɒ���
};
