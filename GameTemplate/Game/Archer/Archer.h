#pragma once
#include "State/IArcherState.h"
#include "Player/Player.h"
class Arrow;
class Archer : public IGameObject
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
	void PlayerFacing();

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
		m_Rotation = rot;
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
private:
	//�U���ł���H
	bool IsAttack();

	//���f����������
	void InitModel();
	
	//�A�j���[�V������������
	void InitAnimetion();

	//�G��������
	void InitSprite();

	//���hp��������
	void InitHpTop();

	//����Hp��������
	void InitHpUnder();

	//�A�j���[�V�����̍X�V
	void AnimationUpdate();


	//��Ԃ̐؂�ւ�
	void UpdateState(int st);

	//�G�̍X�V
	void UpdateSprite();
	
	//hp�̈ʒu���C��
	void HpPosAdjustment();

	//�O�������X�V
	void ForwardUpdate();

	//���f���̍X�V
	void ModelUpdate();

	//�A�j���[�V�����C�x���g��ݒ�
	void OnAnimEvent(const wchar_t* eventName);
	
private:
	SkinModelRender* m_Model = nullptr;				//���f��
	CVector3 m_Position = CVector3::Zero();			//�ʒu
	CVector3 m_SpownPositon = CVector3::Zero();		//�����ʒu
	CQuaternion m_Rotation = CQuaternion::Identity();//��]��
	Animation m_Animation;							//�A�j���[�V����
	AnimationClip m_AnimationClip[State::Num];		//�A�j���[�V�����N���b�v
	IArcherState* m_ActiveState = nullptr;			//���݂̏��
	int m_State = State::Idle;						//���݂̏��
	int m_NextState = State::Idle;					//���̏��
	Player* m_Player = nullptr;						//�v���C���[�̃|�C���^
	CVector3 m_Forward = CVector3::Front();			//�O����

	SpriteRender* m_HpTopSprite = nullptr;		//hp�̃X�v���C�g
	CVector3 m_HpPosition = CVector3::Zero();	//hp�̃X�v���C�g�ʒu
	float m_Hp = 50.0f;							//hp
	const float m_SpriteSize = 0.025f;			//hp�̃T�C�Y�𒲐�

	SpriteRender* m_HpUnderSprite = nullptr;	//hp�̉��ɂ���X�v���C�g
	const float m_height = 150.0f;				//�G�̐g��
	int m_AttackPattarn = 0;					//�ǂ̍U�����肪�������Ă���H

	CharacterController m_CharaCon;				//�L�����R��

	bool m_isAttachArrow = false;
	std::list<Arrow*> m_ArrowList;

	bool m_IsPlayerFacing = true;			//�v���C���[��Ǐ]���邩
};