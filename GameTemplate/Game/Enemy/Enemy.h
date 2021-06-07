#pragma once
#include "character/CharacterController.h"
#include "EnemyAttack.h"
class IEnemyState;
#include "Player/Player.h"
#include "GameSceneFunction/AIProcesing.h"
//�G
class Enemy final :public AIProcesing
{
public:
	//��Ԃ̎�ނ�enum��
enum State {
	Attack,
	Idle,
	Walk,
	Damege,
	Down,
	Num
};
Enemy() {};
~Enemy() {};
public:
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
			if (!m_WalkSound.IsPlaying()) {
				m_WalkSound.Play();
			}
			m_NextState = State::Walk;
		}
	}

	//IdelState�ɑJ�ڂ������Ƃ���p
	void SetIdleState() {
		m_NextState = State::Idle;
	}

	//�v���C���[����̍U��������������Ă΂��
	void HitDamage(const float damege)override;

	//�v���C���[�����ɕ���
	void EnemyWalk() {
		AIWalk();
	}
private:
	//�������ꏊ
	bool Start()override;

	//�A�j���[�V������������
	void AnimetionInit();
	//�X�V
	void Update()override;

	//�A�j���[�V�����C�x���g
	//EnemyAttack������Ă���
	void OnAnimEvent(const wchar_t* eventName);
	
	//�������̔���
	bool IsWalk()const;
	//�U�����邩�𔻒�
	bool IsAttack()const;

	//��]����
	void Rotate()override;

	//�X�e�[�g��؂�ւ���Ƃ��Ɏg�p����
	//enum��state�𗘗p����Ɛ؂�ւ��₷���B�Ă���������
	void ChangeState(int st);

private:

	int m_AttackPattarn = 0;					//�ǂ̍U�����肪�������Ă���H

	AnimationClip m_AniClip[Num];				//�A�j���[�V�����̎��

	int m_State = State::Idle;					//���݂̃X�e�[�g���L������
												//�X�e�[�g��؂�ւ���Ƃ��Ɏg�p����
	IEnemyState* m_ActiveState = nullptr;		//���݂̃X�e�[�g
	int m_NextState = State::Idle;				//���̃X�e�[�g

	CVector3 m_AttackPos = CVector3::Zero();	//�U���̏ꏊ

	Player* m_Player = nullptr;
	SoundSource m_WalkSound;
	SoundSource m_SwingSound;
};
