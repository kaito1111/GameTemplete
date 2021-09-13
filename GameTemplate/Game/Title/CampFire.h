#pragma once
/// <summary>
/// �L�����v�t�@�C���[�̃N���X
/// �^�C�g���Ŏg���Ă���
/// </summary>
class CampFire : public IGameObject
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
	/// ���f���̈ʒu��ݒ肷��
	/// </summary>
	/// <param name="pos">�ʒu</param>
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	/// <summary>
	/// �ŏ����ʂ��擾����
	/// </summary>
	/// <returns>�ŏ�����</returns>
	float GetMinLightPow() {
		float minLightPow = 1000.0f;
		for (float lightPow : m_lightPowArray) {
			minLightPow = min(lightPow, minLightPow);
		}
		return minLightPow;
	}
	/// <summary>
	/// ���̋������擾����
	/// </summary>
	/// <returns>����</returns>
	const float GetLightPow()const {
		return m_LightPower;
	}
	/// <summary>
	/// �ő���ʂ��擾����
	/// </summary>
	/// <returns>�ő����</returns>
	float GetMaxLightPow() {
		float maxLightPow = 1.0f;
		for (float lightPow : m_lightPowArray) {
			maxLightPow = max(lightPow, maxLightPow);
		}
		return maxLightPow;
	}
private:
	SkinModelRender* m_Model = nullptr;			//�L�����v�t�@�C���[�̃��f��
	CVector3 m_Position = CVector3::Zero();		//���f���̈ʒu
	PointLight* m_PointLight = nullptr;			//����
	static const int m_lightPowArraySize = 15;	//���̌��ʃp�^�[���̔z��
	const float m_lightPowArray[m_lightPowArraySize]
		= {
		270.0f,260.0f,220.0,300.0f,40.0f,
		300.0f,280.0f,250.0f,290.0f,240.0f,
		320.0f,260.0f,250.0f,260.0f,270.0f
	};											//���ʃp�^�[�������߂�z��
	int m_currentLigPowNum = 0;					//���ݗL���Ȍ���
	float m_LightPower = 0.0f;					//���̋���
	SoundSource m_Sound;						//�L�����v�t�@�C���[�̉�
	float m_ScaleTime = 0.0f;					//�ǂ̔z���L���ɂ��邩�̕ϐ�
	Effect* m_effect = nullptr;					//���̃G�t�F�N�g
};

