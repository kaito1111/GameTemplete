#pragma once
class Player;
/// <summary>
/// �X�e�[�W���P�߂�N���X
/// </summary>
class ReturnLocatoin final : public IGameObject
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
	/// ���x����ǂݍ��ޗp�̃t�@�C���p�X
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void SetFilePath(wchar_t* filePath) {
		wcscpy(m_FilePath, filePath);
	}
private:
#ifdef _DEBUG
	SkinModelRender* m_Skin = nullptr;	//�G���`�F���͈̔͂�\�������f��
#endif
	CVector3 m_Pos = CVector3::Zero();	//�G���`�F���͈̔͂̒��S
	Player* m_player = nullptr;			//�v���C���[�̃|�C���^
	wchar_t m_FilePath[256] = {};		//���x���̃t�@�C���p�X
};