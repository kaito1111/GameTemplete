#pragma once
class IBossState;
class Player;
#include "GameSceneFunction/AIProcesing.h"
#include "character/CharacterController.h"
#include "BossHpSprite.h"

/// <summary>
/// �{�X�N���X�B
/// </summary>
class Boss final : public AIProcesing
{
	/// <summary>
	/// ��Ԃ�\���񋓌^
	/// </summary>
	enum State {
		Walk,
		Attack,
		NormalRoar,
		AppearanceRoar,
		Down,
		Parry,
		Die,
		StateNum,
	};
public:
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
	/// /�X�e�[�g��ŃA�j���[�V�������v���C����B
	/// </summary>
	/// <param name="nulTime">�f���^�^�C���ɃA�j���[�V�����X�s�[�h���|����</param>
	void PlayAnimation(float nulTime=1.0f) {
		m_Animation.Update(gameTime().GetFrameDeltaTime()*nulTime);
	}
	/// <summary>
	///�A�j���[�V�������Đ����Ă��邩�H
	///�A�j���[�V�������I����Ă邩�ǂ����Ŏg���Ă���
	/// </summary>
	/// <returns>true�ŃA�j���[�V�������Đ���</returns>
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	
	/// <summary>
	/// �U����Ԃֈڍs�ł��邩�H
	/// </summary>
	void IsChengeAttackState();

	
	/// <summary>
	/// ���K��Ԃֈڍs�ł��邩�H
	/// </summary>
	void IsChengeNormalRoar();

	/// <summary>
	/// ���s��Ԃֈڍs
	/// </summary>
	void SetWalkState() {
		m_NextState = State::Walk;
	}

	/// <summary>
	/// �_���[�W���󂯂�
	/// </summary>
	/// <param name="damege">HP������_���[�W�ʁA�܂�U����</param>
	void HitDamage(const float damege)override {
		///hp�����炷
		m_Hp -= damege;
		///�_���[�W���R���̂P�܂Ō�������P�x�����_�E����Ԃɓ���
		if (m_MaxHp / 3 > m_Hp&&IsParyy) {
			///�_���[�W��Ԃ֑J��
			m_NextState = State::Down;
			IsParyy = false;
		}
		///Hp��0�ȉ��ɂȂ����玀��
		if (m_Hp <= 0.0f) {
			m_NextState = State::Die;
			m_Hp = 0;
		}
	}
private:	
	AnimationClip m_AnimationClip[StateNum];	//�A�j���[�V�����N���b�v

	IBossState* m_ActiveState = nullptr;		//��Ԃ̏����������Ă���@�@

	State m_CurrentState = State::StateNum;		//���݂̏��
	State m_NextState = State::AppearanceRoar;	//���̏��

	const float m_CoolTimeRoar = 12.0f;			//���K�����Ă�����K������܂ł̎���
	float m_RoarTime = 0;						//���K���Ă���̌o�ߎ���

#ifdef _DEBUG
	SkinModelRender* m_HitModel = nullptr;		//�f�o�b�O�p�̃��f��
#endif

	BossHpSprite* m_BossSprite = nullptr;		//�{�X��Hp��S������N���X

	SoundSource m_RoarSound;					//���K���ɗ�����
	bool IsParyy = true;						//�p���B���ł��邩�ǂ����i�������j
private:
	/// <summary>
	/// ��Ԃ�ύX����֐�
	/// </summary>
	/// <param name="state">���̏��</param>
	void ChengeState(const State& state);

	/// <summary>
	/// ���f���̉�]����
	/// </summary>
	void Rotate()override;

	/// <summary>
	/// �A�j���[�V�����̏������֐�
	/// </summary>
	void AnimationInit();

	/// <summary>
	/// eventName����A�j���[�V�����C�x���g���g���^�C�~���O���t�b�N���ď���������
	/// </summary>
	/// <param name="eventName">max�œo�^�����C�x���g�̖��O</param>
	void OnAnimEvent(const wchar_t* eventName);

	/// <summary>
	/// BossHpSprite���Ăяo���֐�
	/// </summary>
	void InitSprite();

};

