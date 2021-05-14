#pragma once
#include "Anime.h"
#include "Player/Player.h"
class Attack;
class AIProcesing:public Anime
{
public:
	//�R���X�g���N�^
	AIProcesing() {
		m_player = FindGO<Player>("player");
	}
	//�f�X�g���N�^
	~AIProcesing() {};
	//�v���C���[��ǂ������鏈��
	void AIWalk();
	//�v���C���[���U�����鏈��
	void AIAttack(float damage, float eria,char* AttackName=nullptr);	
	//�v���C���[�̈ʒu���擾
	CVector3 GetPlayerPos() {
		return m_player->GetPosition();
	}
protected:
	Player* m_player = nullptr;//�v���C���[�̃|�C���^
	float AttackReach = 0.0f;	//�U���̌�����r�܂ł̋���
	Attack* m_HaveAttack = nullptr;
};