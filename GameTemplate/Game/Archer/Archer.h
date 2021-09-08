#pragma once
#include "State/IArcherState.h"
#include "GameSceneFunction/AIProcesing.h"

/// <summary>
/// Archer�N���X���g����N���X
/// </summary>
class Arrow;

/// <summary>
/// �A�[�`���[�N���X
/// </summary>
class Archer final : public AIProcesing
{
	/// <summary>
	/// ��Ԃ�\���񋓌^
	/// </summary>
	enum State {
		Idle,
		Attack,
		Damage,
		Deth,
		Num
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
	bool Start()override;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
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
	void OnDestroy()override;

	/// <summary>
	/// �v���C���[�̂�������Ɍ���
	/// </summary>
	void Rotate();

	/// <summary>
	/// �A�j���[�V�������Đ����Ă��邩
	/// </summary>
	/// <returns>true�ŃA�j���[�V����������Ă���</returns>
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	/// <summary>
	/// �U���̏�ԂɑJ�ڂ��邩
	/// </summary>
	void TryAttackState() {
		//�U���̏�ԂɑJ�ڂł��邩
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	/// <summary>
	/// �ҋ@��Ԃ֑J�ڂ���
	/// </summary>
	const void SetIdleState() {
		m_NextState = State::Idle;
	}

	/// <summary>
	/// �����ʒu��ݒ肷��
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	const void SetSpownPosition(const CVector3& pos) {
		m_SpownPositon = pos;
	}

	/// <summary>
	/// ��]�ʂ�ݒ肷��
	/// </summary>
	/// <param name="rot">��]��</param>
	const void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}
	/// <summary>
	/// �X�P���g���ɐݒ肳��Ă���A�^�b�`�{�[������A��̈ʒu�Ɖ�]���v�Z����
	/// </summary>
	void CalcArrowPosAndRotationFromAttachBone(CVector3& pos, CQuaternion& rot, const wchar_t* AttachName, const wchar_t* TargetName);
	/// <summary>
	/// �����������{�[�����擾����B
	/// </summary>
	/// <returns></returns>
	Bone* GetArrowAttachBone() const
	{
		return m_Model->GetModel().FindBone(L"arrow_attach");
	}
	Bone* GetArrowAttachBone2() const
	{
		return m_Model->GetModel().FindBone(L"arrow_attach");
	}

	/// <summary>
	/// ����|�̍��ɃA�^�b�`���邩
	/// </summary>
	/// <returns>true�Ȃ�A�^�b�`����</returns>
	bool IsAttachArrow()const {
		return m_isAttachArrow;
	}

	/// <summary>
	/// ����A�[�`���[�̃��X�g����폜
	/// </summary>
	void ArrowListPop() {
		if (m_ArrowList.size() != 0) {
			m_ArrowList.pop_front();
		}
	}

	/// <summary>
	/// �v���C���[�̕����Ɍ����Ă��邩�ǂ���
	/// </summary>
	/// <returns>true�Ńv���C���[�̕����Ɍ���</returns>
	bool IsFacingFlag()const{
		return m_IsPlayerFacing;
	}

	/// <summary>
	/// �v���C���[�̕����Ɍ���
	/// </summary>
	void SetFacingFlag() {
		m_IsPlayerFacing = true;
	}

	/// <summary>
	/// �U����H�炤�ƌĂ΂��
	/// </summary>
	/// <param name="damege">�_���[�W��</param>
	void HitDamage(const float damege)override;
private:
	/// <summary>
	/// �U���ł���H
	/// </summary>
	/// <returns>�U���ł���Ȃ�true���Ԃ�</returns>
	bool IsAttack();

	/// <summary>
	/// ���f����������
	/// </summary>
	void InitModel();
	
	/// <summary>
	/// �A�j���[�V������������
	/// </summary>
	void InitAnimetion();

	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	void AnimationUpdate();

	/// <summary>
	/// ��Ԃ�ύX����֐�
	/// </summary>
	/// <param name="state">���̏��</param>
	void UpdateState(int st);

	/// <summary>
	/// eventName����A�j���[�V�����C�x���g���g���^�C�~���O���t�b�N���ď���������
	/// </summary>
	/// <param name="eventName">max�œo�^�����C�x���g�̖��O</param>
	void OnAnimEvent(const wchar_t* eventName);
	
private:
	CVector3 m_SpownPositon = CVector3::Zero();		//�����ʒu

	AnimationClip m_AnimationClip[State::Num];		//�A�j���[�V�����N���b�v

	IArcherState* m_ActiveState = nullptr;			//���݂̏��
	int m_State = State::Idle;						//���݂̏��
	int m_NextState = State::Idle;					//���̏��

	int m_AttackPattarn = 0;						//�ǂ̍U�����肪�������Ă���H

	bool m_isAttachArrow = false;					//���ɂ��^�C�~���O���ǂ���
	std::list<Arrow*> m_ArrowList;					//���ł��тɃ��X�g�ɐς�
	Arrow* m_HasArrow = nullptr;					//���łr�����ǂ���

	bool m_IsPlayerFacing = true;					//�v���C���[��Ǐ]���邩

	SoundSource m_Shot;								//���ł������̉�
	SoundSource m_Draw;								//��������Ă���Ƃ��̉�
};