#pragma once
#include "Player/Player.h"
#include "level/Level.h"
/// <summary>
/// �v���C���[�N���X�̐e�N���X
/// </summary>
class PlayerSpowner final : public IGameObject
{
public:
	
	/// <summary>
	/// ���x���Ń��[�h����t�@�C���p�X��Game�N���X�Őݒ�
	/// </summary>
	/// <param name="fileName">���[�h�������t�@�C���p�X</param>
	void SetFilePath(wchar_t* fileName) {
		wcscpy_s(m_filePath, fileName);
	}

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
	void OnDestroy()override final;

private:
	Player* m_player = nullptr;		//�v���C���[�|�C���^
	Level m_level;					//���x��
	wchar_t m_filePath[256] = {};	//���x���Ń��[�h����t�@�C���p�X
};

