#pragma once
class Fade;
class Stage;
class Player;
class GameCamera;
class CampFire;
/// <summary>
/// �^�C�g����炷
/// </summary>
class Title final : public IGameObject
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

private:
	SpriteRender* m_TitleSprite = nullptr;	//PleaseAnyButton�Ə����ꂽ�X�v���C�g
	Fade* m_fade = nullptr;					//�V�[���؂�ւ����Ɏg���t�F�[�h
	Stage* m_Stage = nullptr;				//�X�e�[�W�̃|�C���^
	Player* m_Player = nullptr;				//�v���C���[�̃|�C���^
	GameCamera* m_camera = nullptr;			//�J�����̃|�C���^
	CampFire* m_camp = nullptr;				//�L�����v�t�@�C���[�̃|�C���^
	float m_Alpha = 0.5f;					//�X�v���C�g�̓����x
};

