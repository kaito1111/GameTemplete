#pragma once
#include "Anime.h"
#include "Player/Player.h"
class Attack;
/// <summary>
/// �G�L������{�X���g���������܂Ƃ߂�����
/// �p�����g���ė��p����
/// </summary>
class AIProcesing:public Anime
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	AIProcesing() {
		m_player = FindGO<Player>("player");
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AIProcesing() ;

	/// <summary>
	/// �v���C���[��ǂ������鏈��
	/// </summary>
	void AIWalk();

	/// <summary>
	/// �v���C���[���U�����鏈��
	/// </summary>
	void AIAttack(float damage, float eria,char* AttackName=nullptr);	

	/// <summary>
	/// �v���C���[�̈ʒu���擾
	/// </summary>
	/// <returns>�v���C���[�̈ʒu��Ԃ�</returns>
	CVector3 GetPlayerPos() {
		return m_player->GetPosition();
	}

	/// <summary>
	/// �v���C���[��������Hp�������Ȃ�����
	/// </summary>
	void UpdateHpAlpha();

	/// <summary>
	/// enemy������ł���U��������ł͒x���̂�
	/// ���I�ɏ�����悤�ɂ���
	/// </summary>
	void DeleteAttack();
protected:
	Player* m_player = nullptr;		//�v���C���[�̃|�C���^
	float AttackReach = 50.0f;		//�U���̌�����r�܂ł̋���
	Attack* m_HaveAttack = nullptr;	//���̍U���N���X�𗘗p���čU������
	float m_HpAlhpa = 0.0;			//�����ɂ���Ď��F�ł��邩������
	float m_deltaTime = 0.0f;		//Hp�������Ȃ��Ȃ鎞��
};