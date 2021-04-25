#pragma once
#include "character/characterController.h"
class Character :public IGameObject
{
public:
	~Character() {};


	//�����ʒu��ݒ�
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}

	void Init(wchar_t* filePath, float radius, float hight, const CVector3& pos);

	virtual void Rotate() = 0;

	//��]�ʂ�ݒ�
	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}

	//�ʒu���擾
	const CVector3& GetPosition() {
		return m_Pos;
	}

	//�����œ���
	void Move(CVector3& move);
protected:
	SkinModelRender* m_Model = nullptr;			//�G�̃��f��
	CVector3 m_Pos = CVector3::Zero();			//�G�̈ʒu
	CQuaternion m_Rot = CQuaternion::Identity();//�G�̉�]
	CVector3 m_Scale = CVector3::One()*10.0f;	//�G�̑傫��
	CharacterController m_CharaCon;				//�L�����R��

	CVector3 m_MoveSpeed = CVector3::Zero();	//�ړ���
	CVector3 m_forward = CVector3::Front();		//�O����
	CVector3 m_SpownPosition = CVector3::Zero();//�����ʒu
};

