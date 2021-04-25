#pragma once
#include "character/characterController.h"
class Character :public IGameObject
{
public:
	~Character() {
		DeleteGO(m_Model);
	};


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
protected:
	SkinModelRender* m_Model = nullptr;			//�G�̃��f��
	CVector3 m_ModelPos = CVector3::Zero();			//�G�̈ʒu
	CQuaternion m_ModelRot = CQuaternion::Identity();//�G�̉�]
	CVector3 m_ModelScale = CVector3::One();	//�G�̑傫��
	CharacterController m_CharaCon;				//�L�����R��

	CVector3 m_MoveSpeed = CVector3::Zero();	//�ړ���
	CVector3 m_forward = CVector3::Front();		//�O����
	CVector3 m_SpownPosition = CVector3::Zero();//�����ʒu
};

