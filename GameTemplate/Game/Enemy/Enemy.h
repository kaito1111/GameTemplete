#pragma once
#include "character/CharacterController.h"
#include "EnemyAttack.h"
class IEnemyState;
#include "Player/Player.h"
//�G
class Enemy : public IGameObject
{
public:
enum State {
	Attack,
	Idle,
	Walk,
	Damege,
	Down,
	Num
};
	Enemy();
	~Enemy();
	//�G���������u�ԂɌĂ΂��
	void OnDestroy()override;
public:
	//�ʒu���擾
	CVector3 GetPlayerPos() {
		return m_Player->GetPosition();
	}

	//�v���C���[����̍U��������������Ă΂��
	void HitDamege(const float damege);

	//�ʒu���擾
	const CVector3& GetPosition() {
		return m_Pos;
	}
	//�A�j���[�V�������Đ�
	//enum��State���g���ƕ֗��B����
	void PlayAnimation(State st) {
		m_Animation.Play(st, 0.2f);
	}
	//�A�j���[�V�������Đ����H
	bool IsPlayingAnimation() const{
		return m_Animation.IsPlaying();
	}


	//�v���C���[���U�����邩����
	void TryChangeAttackState() {
		//true�ōU��
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	//�v���C���[��ǂ������邩���ׂ�
	void TryChangeWalk() {
		//true�ŕ���
		if (IsWalk()) {
			m_NextState = State::Walk;
		}
	}

	//IdelState�ɑJ�ڂ������Ƃ���p
	void SetIdleState() {
		m_NextState = State::Idle;
	}

	//�����œ���
	void Move(CVector3 move);

	//�����ʒu��ݒ�
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}
	//��]�ʂ�ݒ�
	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}
private:
	//�������ꏊ
	bool Start()override;

	//���f����������
	void SkinModelInit();

	//�L�����R����������
	//1�s�ŏI��邩�疳�ʂ����ǂ킩��₷�����邽�߁@
	void CharaConInit();

	//HP�X�v���C�g��������
	void HpSpriteInit();
	//HP��G�̂�����Ə�ɒu��
	//Hp�̈ʒu����_�ɍ��킹�ďC��
	void HpPosAdjustment();
	//TopSprite��������
	void HpTopSpriteInit(const float sizeY,const CVector3& scale);
	//UnderSprite��������
	void HpUnderSprite(const float sizeY, const CVector3& scale);

	//�A�j���[�V������������
	void AnimetionInit();
	//�X�V
	void Update()override;

	//�G�̉�]�̍X�V
	void EnemyRot();
	//�A�j���[�V�����C�x���g
	//EnemyAttack������Ă���
	void OnAnimEvent(const wchar_t* eventName);
	//�X�v���C�g���X�V
	void UpdateSprite();
	
	//�������̔���
	bool IsWalk()const;
	//�U�����邩�𔻒�
	bool IsAttack()const;


	//�X�e�[�g��؂�ւ���Ƃ��Ɏg�p����
	//enum��state�𗘗p����Ɛ؂�ւ��₷���B�Ă���������
	void ChangeState(int st);

	//
private:
	SkinModelRender* m_Skin = nullptr;			//�G�̃��f��
	CVector3 m_Pos = CVector3::Zero();			//�G�̈ʒu
	CQuaternion m_Rot = CQuaternion::Identity();//�G�̉�]
	CVector3 m_Scale = CVector3::One()*10.0f;	//�G�̑傫��
	CharacterController m_CharaCon;				//�L�����R��
	Player* m_Player = nullptr;					//�v���C���[

	CVector3 m_MoveSpeed = CVector3::Zero();	//�ړ���

	SpriteRender* m_HpTopSprite = nullptr;		//hp�̃X�v���C�g
	CVector3 m_HpPosition = CVector3::Zero();	//hp�̃X�v���C�g�ʒu
	float m_Hp = 62.5f;							//hp
	const float m_SpriteSize = 0.025f;			//hp�̃T�C�Y�𒲐�

	SpriteRender* m_HpUnderSprite = nullptr;	//hp�̉��ɂ���X�v���C�g
	const float m_height = 150.0f;				//�G�̐g��
	int m_AttackPattarn = 0;					//�U�����肪�������Ă���H

	Animation m_Animation;						//�A�j���[�V����
	AnimationClip m_AniClip[Num];				//�A�j���[�V�����̎��

	int m_State = State::Idle;					//���݂̃X�e�[�g���L������
												//�X�e�[�g��؂�ւ���Ƃ��Ɏg�p����
	IEnemyState* m_ActiveState = nullptr;		//���݂̃X�e�[�g
	int m_NextState = State::Idle;				//���̃X�e�[�g

	CVector3 m_forward = CVector3::Front();		//�O����
	CVector3 m_AttackPos = CVector3::Zero();	//�U���̏ꏊ

	EnemyAttack* attack = nullptr;				//�U������

	CVector3 m_SpownPosition = CVector3::Zero();//�����ʒu
};
