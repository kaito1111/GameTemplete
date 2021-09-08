#pragma once
/// <summary>
/// ���񂾎��ɌĂԃN���X
/// </summary>
class DieSprite final : public IGameObject
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
	bool Start()override;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
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
	void OnDestroy()override;

private:
	SpriteRender* m_DieSprite = nullptr;				//�_�C�X�v���C�g
	float m_DieAlpha = 0.0f;							//�_�C�X�v���C�g�̓����x

	SpriteRender* m_LogoSprite = nullptr;				//���S�X�v���C�g
	float m_LogoAlpha = 0.0f;							//���S�X�v���C�g�̓����x

	SpriteRender* m_PlayerDieChoicesSprite = nullptr;	//�I�����̃X�v���C�g
	float m_ChoicesAlpha = 0.0f;						//�I�����̃X�v���C�g�̓����x

	SpriteRender* m_ChoicesIConSprite = nullptr;		//���̃X�v���C�g
	CVector3 m_IConPos = { -100.0f,50.0f,0.0f };		//���̈ʒu

	bool IsReset = false;								//�I������I�񂾂��ǂ����̃t���O
};