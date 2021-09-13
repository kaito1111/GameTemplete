#pragma once
/// <summary>
/// ��
/// </summary>
class Floor final : public IGameObject
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
	bool Start() override final;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update() override final;
	/// <summary>
	///	���f���̈ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�ʒu</param>
	void SetPosition(const CVector3& pos) {
		m_Pos = pos;
	}
	/// <summary>
	/// ���f���̉�]�ʂ�ݒ�
	/// </summary>
	/// <param name="rot">��]��</param>
	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}

private:
	SkinModelRender* m_Model = nullptr;				//���̃��f��
	CVector3 m_Pos = CVector3::Zero();				//���f���̈ʒu
	CQuaternion m_Rot = CQuaternion::Identity();	//���f���̉�]��
	CVector3 m_Scale = CVector3::One();				//���f���̑傫��
};