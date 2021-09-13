#pragma once
#include "physics/PhysicsStaticObject.h"
/// <summary>
/// �ǂ̃N���X
/// </summary>
class Wall final : public IGameObject
{
public:
	/// <summary>
	/// �C���X�^���X�����������ƁA��x�����Ă΂��J�n����
	/// </summary>
	/// <remarks>
	/// Unity��Start()�֐��̎d�l�ɏ����B
	/// </remarks>
	/// <returns>
	/// true���A���Ă�����A�����������B
	/// �����t���[���ɂ킽���ď��������������ꍇ�́A
	/// �����������܂�false��Ԃ��B
	/// </returns>
	bool Start()override final;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override final;
	/// <summary>
	/// ���f���̈ʒu��ݒ肷��
	/// </summary>
	/// <param name="Pos">�ʒu</param>
	const void SetPosition(const CVector3& Pos) {
		m_Pos = Pos;
	}
	/// <summary>
	/// ���f���̉�]�ʂ�ݒ肷��
	/// </summary>
	/// <param name="Rot">��]��</param>
	const void SetRotation(const CQuaternion& Rot) {
		m_Rot = Rot;
	}
private:
	SkinModelRender* m_Model = nullptr;				//�ǂ̃��f��
	CVector3 m_Pos = CVector3::Zero();				//���f���̈ʒu
	CQuaternion m_Rot = CQuaternion::Identity();	//���f���̉�]��
	PhysicsStaticObject m_Pysics;					//�ÓI�����I�u�W�F�N�g
};