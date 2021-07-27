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
	~AIProcesing() ;
	//�v���C���[��ǂ������鏈��
	void AIWalk();
	//�v���C���[���U�����鏈��
	void AIAttack(float damage, float eria,char* AttackName=nullptr);	
	//�v���C���[�̈ʒu���擾
	CVector3 GetPlayerPos() {
		return m_player->GetPosition();
	}
	//�v���C���[��������Hp�������Ȃ�����
	void UpdateHpAlpha();
protected:
	Player* m_player = nullptr;//�v���C���[�̃|�C���^
	float AttackReach = 50.0f;	//�U���̌�����r�܂ł̋���
	Attack* m_HaveAttack = nullptr;
	float m_HpAlhpa = 0.0;		//�����ɂ���Ď��F�ł��邩������
	float m_deltaTime = 0.0f;	//Hp�������Ȃ��Ȃ鎞��
};