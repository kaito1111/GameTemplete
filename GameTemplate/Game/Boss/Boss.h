#pragma once
class IBossState;
class Player;
#include "GameSceneFunction/AIProcesing.h"
#include "character/CharacterController.h"
class Boss : public AIProcesing
{
	//���
	enum State {
		Walk,
		Attack,
		NormalRoar,
		AppearanceRoar,
		Die,
		StateNum,
	};
public:
	~Boss() {};//�f�X�X�g���N�^
	


	bool Start()override;//�������֐����Ăԏꏊ
	void Update()override;//�X�V�֐����Ăԏꏊ

	//�X�e�[�g��ŃA�j���[�V�������v���C����B
	void PlayAnimation() {
		m_Animation.Update(gameTime().GetFrameDeltaTime());
	}
	
	//�A�j���[�V�������Đ����Ă��邩�H
	//�A�j���[�V�������I����Ă邩�ǂ����Ŏg���Ă���
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	//�U����Ԃֈڍs�ł��邩�H
	void IsChengeAttackState();

	//���K��Ԃֈڍs�ł��邩�H
	void IsChengeNormalRoar();

	//���s��Ԃֈڍs
	void SetWalkState() {
		m_NextState = State::Walk;
	}
private:	
	AnimationClip m_AnimationClip[StateNum];//�A�j���[�V�����N���b�v

	IBossState* m_ActiveState = nullptr;	//��Ԃ̏����������Ă���@�@

	State m_CurrentState = State::AppearanceRoar;	//���݂̏��
	State m_NextState = State::Walk;		//���̏��

	const float m_CoolTimeRoar = 500;	//���K�����Ă�����K������܂ł̎���
	float m_RoarTime = 0;				//���K���Ă���̌o�ߎ���

	SkinModelRender* m_HitModel = nullptr;		//�f�o�b�O�p�̃��f��
private:
	//�X�e�[�g��ύX����֐�
	void ChengeState(const State& state);
	//���f���̉�]����
	void Rotate()override;
	//�A�j���[�V�������������֐�
	void AnimationInit();
};

