#pragma once

class Effect : public ksEngine::IGameObject
{
public:
	Effect(){}
	~Effect(){
		Release();
	}
	/// <summary>
	/// ���
	/// </summary>
	void Release();
	/// <summary>
	/// �G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="filePath">�Đ�����G�t�F�N�g�̃t�@�C���p�X</param>
	void Play(const wchar_t* filePath);
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	/// <summary>
	/// ��]�̐ݒ�
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot) {
		m_Rotarion = rot;
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const CVector3& scale) {
		m_Scale = scale;
	}
	/// <summary>
	/// �G�t�F�N�g���Đ���������
	/// </summary>
	/// <returns></returns>
	bool IsPlay()const;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

private:
	Effekseer::Effect*  m_effect = nullptr;
	Effekseer::Handle   m_handle = -1;
	CVector3			m_Position = CVector3::Zero();			//���W
	CQuaternion			m_Rotarion = CQuaternion::Identity();	//��]
	CVector3			m_Scale = CVector3::One();				//�g�嗦
};

