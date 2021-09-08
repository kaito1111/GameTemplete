#pragma once
/// <summary>
/// ����ƂȂ�N���X�Ɍp��������N���X
/// ���̃N���X�Ō����̐؂�ւ�������i�������j
/// 
/// </summary>
class IWeapon
{
public:
	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual	~IWeapon() {};

	/// <summary>
	/// �C���X�^���X���Ă΂��ƈ�x�����Ă΂�鏃�����z�֐��B
	/// �������֐����g��Ȃ����͑�̂Ȃ��̂ŁA
	/// ���������āA��΂ɌĂԂ悤�ɂ��Ă���
	/// </summary>
	virtual void Start() = 0;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// �X�V�֐����g��Ȃ����͑�̂Ȃ��̂ŁA
	/// ���������āA��΂ɌĂԂ悤�ɂ��Ă���
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �C���X�^���X���j�������ƈ�x�����Ă΂�鏃�����z�֐��B
	/// �j���֐����g��Ȃ����͑�̂Ȃ��̂ŁA
	/// ���������āA��΂ɌĂԂ悤�ɂ��Ă���
	/// </summary>
	virtual void Delete() = 0;
	/// <summary>
	/// ����̈ʒu��ݒ肷��
	/// </summary>
	/// <param name="pos">����̈ʒu</param>
	void SetPosition(CVector3 pos) {
		m_Position = pos;
	}
	/// <summary>
	/// ����̉�]��ݒ肷��
	/// </summary>
	/// <param name="rot">����̉�]</param>
	void SetRotation(CQuaternion rot) {
		m_Rotation = rot;
	}
	/// <summary>
	/// ���f�����擾����C
	/// </summary>
	/// <returns>���f��</returns>
	SkinModelRender* GetModel() {
		return m_model;
	}
protected:
	CVector3 m_Position = CVector3::Zero();				//���탂�f���̈ʒu
	CQuaternion m_Rotation = CQuaternion::Identity();	//���탂�f���̉�]
	SkinModelRender* m_model = nullptr;					//����̃��f��

};

