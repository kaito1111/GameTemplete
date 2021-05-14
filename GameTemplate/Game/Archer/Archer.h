#pragma once
#include "State/IArcherState.h"
#include "GameSceneFunction/AIProcesing.h"

class Arrow;
class Archer : public AIProcesing
{
	//��Ԃ̎�ނ�enum��
	enum State {
		Idle,
		Attack,
		Damage,
		Deth,
		Num
	};
public:
	~Archer() {};
	//������
	bool Start()override;
	//�X�V
	void Update()override;
	//���񂾂Ƃ��ɌĂ΂��֐�
	void OnDestroy()override;

	//�v���C���[�̂�������Ɍ���
	void Rotate();

	//�A�j���[�V�������Đ����Ă��邩
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	//�U���̏�ԂɑJ�ڂ��邩
	void TryAttackState() {
		//�U���̏�ԂɑJ�ڂł��邩
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	//�ҋ@��Ԃ֑J�ڂ���
	void SetIdleState() {
		m_NextState = State::Idle;
	}

	//�����ʒu��ݒ肷��
	void SetSpownPosition(const CVector3& pos) {
		m_SpownPositon = pos;
	}

	//��]�ʂ�ݒ肷��
	void SetRotation(const CQuaternion& rot) {
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
	//�|�̍��ɃA�^�b�`���邩
	bool IsAttachArrow()const {
		return m_isAttachArrow;
	}
	//�|���A�[�`���[�̃��X�g����폜
	void ArrowListPop() {
		m_ArrowList.pop_front();
	}

	bool IsFacingFlag()const{
		return m_IsPlayerFacing;
	}

	void SetFacingFlag() {
		m_IsPlayerFacing = true;
	}

	void HitDamage(const float damege)override;
private:
	//�U���ł���H
	bool IsAttack();

	//���f����������
	void InitModel();
	
	//�A�j���[�V������������
	void InitAnimetion();

	//�A�j���[�V�����̍X�V
	void AnimationUpdate();


	//��Ԃ̐؂�ւ�
	void UpdateState(int st);

	//�A�j���[�V�����C�x���g��ݒ�
	void OnAnimEvent(const wchar_t* eventName);
	
private:
	CVector3 m_SpownPositon = CVector3::Zero();		//�����ʒu

	AnimationClip m_AnimationClip[State::Num];		//�A�j���[�V�����N���b�v

	IArcherState* m_ActiveState = nullptr;			//���݂̏��
	int m_State = State::Idle;						//���݂̏��
	int m_NextState = State::Idle;					//���̏��

	int m_AttackPattarn = 0;					//�ǂ̍U�����肪�������Ă���H

	bool m_isAttachArrow = false;
	std::list<Arrow*> m_ArrowList;
	Arrow* m_HasArrow = nullptr;

	bool m_IsPlayerFacing = true;			//�v���C���[��Ǐ]���邩
};