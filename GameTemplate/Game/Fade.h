#pragma once
class Boss;
/// <summary>
/// �t�F�[�h�N���X
/// �V�[���؂�ւ����ɌĂ΂��N���X
/// </summary>
class Fade final :public IGameObject
{
private:
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
public:
	/// <summary>
	///	�t�F�[�h�̓����x���擾
	/// </summary>
	/// <returns></returns>
	const float GetAlpha()const {
		return m_Alpha;
	}
private:
	SpriteRender* m_FadeSprite = nullptr;				//�t�F�[�h��S������X�v���C�g
	float m_Alpha = 0.0f;								//�X�v���C�g�̓����x
	float m_StayCount = 0;								//�^���Âɂ��鎞�ԁi�������Ȃǂ����̃^�C�~���O�ł���j
	SpriteRender* m_LodingSprite = nullptr;				//�E���ł��邮�����Ă�X�v���C�g
	float m_Angle = 0.0f;								//�E���̃X�v���C�g�̉�]��
	CVector3 m_LodingSpritePos = {800.0f,-200.0f,0.0f};	//�E���̃X�v���C�g�̈ʒu
};

