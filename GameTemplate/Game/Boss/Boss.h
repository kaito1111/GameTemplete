#pragma once
class IBossState;
class Player;
#include "GameSceneFunction/AIProcesing.h"
#include "character/CharacterController.h"
#include "BossHpSprite.h"
class Boss final : public AIProcesing
{
	//���
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
	~Boss() {};//�f�X�X�g���N�^

	bool Start()override;//�������֐����Ăԏꏊ
	void Update()override;//�X�V�֐����Ăԏꏊ
	void OnDestroy()override;
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

	//�_���[�W���󂯂�
	void HitDamage(const float damege)override {
		//hp�����炷
		m_Hp -= damege;
		//�_���[�W���R���̂P�܂Ō�������P�x�����_�E����Ԃɓ���
		if (m_MaxHp / 3 > m_Hp&&IsParyy) {
			//�_���[�W��Ԃ֑J��
			m_NextState = State::Down;
			IsParyy = false;
		}
		//Hp��0�ȉ��ɂȂ����玀��
		if (m_Hp <= 0.0f) {
			m_NextState = State::Die;
			m_Hp = 0;
		}
	}
private:	
	AnimationClip m_AnimationClip[StateNum];//�A�j���[�V�����N���b�v

	IBossState* m_ActiveState = nullptr;	//��Ԃ̏����������Ă���@�@

	State m_CurrentState = State::AppearanceRoar;	//���݂̏��
	State m_NextState = State::Walk;		//���̏��

	const float m_CoolTimeRoar = 10;	//���K�����Ă�����K������܂ł̎���
	float m_RoarTime = 0;				//���K���Ă���̌o�ߎ���

#ifdef _DEBUG
	SkinModelRender* m_HitModel = nullptr;		//�f�o�b�O�p�̃��f��
#endif

	BossHpSprite* m_BossSprite = nullptr;

	SoundSource m_RoarSound;
private:
	//�X�e�[�g��ύX����֐�
	void ChengeState(const State& state);
	//���f���̉�]����
	void Rotate()override;
	//�A�j���[�V�������������֐�
	void AnimationInit();

	void OnAnimEvent(const wchar_t* eventName);

	//���K�������X�V����֐�
	void RoarUpdate();

	void InitSprite();

	bool IsParyy = true;	//�p���B���ł��邩�ǂ���
};

