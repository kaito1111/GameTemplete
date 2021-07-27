#pragma once
#include "character/characterController.h"
class Character :public IGameObject
{
public:
	enum HpScale {
		PlayerHP,
		EnemyHP,
		BossHP,
		Num
	};
	~Character() ;

	void Destroy();

	//�����ʒu��ݒ�
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}

	//���f���̏�����
	void CharacterInit(wchar_t* filePath, float radius, float hight, const CVector3& pos);

	//��]�������e���ݒ�
	virtual void Rotate() = 0;

	//��]�ʂ�ݒ�
	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}

	//�ʒu���擾
	const CVector3& GetPosition() {
		return m_ModelPos;
	}

	//�����œ���
	void Move(CVector3& move);

	//���f�����X�V����
	void CharacterModelUpdate();

	//�O�����̍X�V������
	virtual void ForwardUpdate();

	//�ړ��ʂ��擾
	CVector3 GetMoveSpeed()const {
		return m_MoveSpeed;
	}

	CQuaternion GetRot() {
		return m_ModelRot;
	}
	
	//hp�ƍő�Hp��ݒ肵�Ă���
	void InitHpSprite(const float maxHp,const float hp, HpScale hpScale);

	//�X�v���C�g��hp�̎c��Ƃ����v�Z���Ă���
	void SpriteUpdate();

	//�U���������������ɌĂ΂��
	//�֐����ɃX�e�[�g��ύX���鏈��������̂ŏ������z�֐��ɂ���
	virtual	void HitDamage(const float damege) = 0;

	void Heal();

private:
	void SpriteInit(SpriteRender*& SpriteP,wchar_t* fileName);
	void HpPosAdjustment();
protected:
	SkinModelRender* m_Model = nullptr;			//���f��
	CVector3 m_ModelPos = CVector3::Zero();			//���f���̈ʒu
	CQuaternion m_ModelRot = CQuaternion::Identity();//���f���̉�]
	CVector3 m_ModelScale = CVector3::One();	//���f���̑傫��
	CharacterController m_CharaCon;				//�L�����R��

	CVector3 m_MoveSpeed = CVector3::Zero();	//�ړ���
	CVector3 m_forward = CVector3::Front();		//�O����
	CVector3 m_SpownPosition = CVector3::Zero();//�����ʒu

	SpriteRender* m_HpUnderSprite = nullptr;
	SpriteRender* m_HpTopSprite = nullptr;
	CVector3 m_HpPosition = CVector3::Zero();
	float m_Hp = 0.0f;
	float m_MaxHp = 0.0f;
	float m_Hight = 0.0f;
	HpScale m_HpScale;
	float m_HpScaleList[HpScale::Num] = { 100.0f,100.0f,120.f };
	//�X�v���C�g�̊�_�����炵�Ă���̂�
	//���̃Y�����C��
	float m_spriteFix = -50.0f;

	CVector3 m_Left = CVector3::Left();
	SpriteRender* m_HpTopTranslucentSprite = nullptr;  //Hp�̔������X�v���C�g
	float m_TranslucentScale = 1.0f;
	float m_HoldTimer = 3.0f;
};

