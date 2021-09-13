#pragma once
class Player;
class Fade;
/// <summary>
/// �G���`�F����S������N���X
/// </summary>
class SceneChangeLocation final : public IGameObject
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
	/// ���f���̈ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�ʒu</param>
	void SetPosition(const CVector3& pos) {
		m_Pos = pos;
	}
	/// <summary>
	/// ���݂̃X�e�[�W��ǂݍ��ރt�@�C���p�X
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void SetFilePath(const wchar_t* filePath) {
		wcscpy(m_FilePath, filePath);
	}
private:
	CVector3 m_Pos = CVector3::Zero();	//�G���`�F���͈̔͂̒��S
	Player* m_player = nullptr;			//�v���C���[�|�C���^
#ifdef _DEBUG
	SkinModelRender* m_Skin = nullptr;	//�G���`�F���͈̔͂�\�������f��
#endif
	wchar_t m_FilePath[256] = {};		//���݂̃X�e�[�W�̃t�@�C���p�X
	Fade* m_Fade = nullptr;				//�G���`�F�����ɗ����t�F�[�h
};

