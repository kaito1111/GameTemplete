#pragma once
#include "Enemy/Enemy.h"
#include "level/level.h"
/// <summary>
/// �G�l�~�[�̐e�N���X
/// </summary>
class EnemySpawner final : public IGameObject
{
public:
	/// <summary>
	/// �G�̏o�Ă���t�@�C���p�X�����[�h
	/// </summary>
	/// <param name="fileName">�t�@�C���p�X</param>
	void SetFilePath(const wchar_t* fileName) {
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
	bool Start()override;

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
	Level m_Level;						//���x��
	std::vector<Enemy*> m_EnemyList;	//�G�̃��X�g
	wchar_t m_filePath[256] = {};		//���x�������[�h����p�̃t�@�C���p�X
};

