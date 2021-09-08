#pragma once
class Candle: public IGameObject
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
	/// �C���X�^���X���j������鎞�ɌĂ΂��֐��B
	/// </summary>
	/// <remarks>
	/// �{�G���W���Ŏ������Ă���A�Q�[���I�u�W�F�N�g���폜����
	/// DeleteGO�֐��́A�����ɃC���X�^���X���폜����킯�ł͂Ȃ��A
	/// 1�t���[���x��ăC���X�^���X���폜�����B
	/// ���̂��߁A�f�X�g���N�^�̌Ăяo�����ADeleteGO�̌Ăяo������1�t���[���x��邱�ƂƂȂ�B
	/// DeleteGO���Ă΂ꂽ�^�C�~���O�ŁA�s�������I��������OnDestroy()�ɋL�q����B
	/// </remarks>
	void OnDestroy()override final;

	/// <summary>
	/// ���f���ʒu��ݒ�
	/// </summary>
	/// <param name="pos">���f���̈ʒu</param>
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	/// <summary>
	/// ���f���̉�]��ݒ�
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot) {
		m_Rotation = rot;
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Position = CVector3::Zero();
	CQuaternion m_Rotation = CQuaternion::Identity();
	PointLight* m_PointLightRed = nullptr;//�O���̌����Č�����
	float m_LightPower = 200.0f;
	float a = -8.0f; 
	CVector3 LightPos = CVector3::Zero();

	PointLight* m_PointLightYellow = nullptr;//�����̌����Č�����
	Effect* m_Effect = nullptr;
};