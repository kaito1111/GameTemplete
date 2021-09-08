#pragma once
class Fade;
/// <summary>
/// �{�X��|�����Ƃ��ɃX�v���C�g��
/// �Q�[�����[�v�������Ǘ����Ă���N���X
/// </summary>
class HuntedSprite final :public IGameObject
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
	SpriteRender* m_HuntSprite = nullptr;	//�n���g�X�v���C�g
	SpriteRender* m_BrackSprite = nullptr;	//�n���g�X�v���C�g���o�Ă���Ƃ���
											//�����������Ƃ����Â�����G�t�F�N�g�I�ȃX�v���C�g
	float m_HuntAlpha = 0.0f;				//�n���g�X�v���C�g�̓����x

	bool m_ReSet = false;					//�I������I�񂾂��ǂ����̃t���O
	SoundSource m_HuntSound;				//�N���A���̉��y
};