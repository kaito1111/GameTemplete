#pragma once

#include "Player/Player.h"
class Stage;
class GameCamera;
#include "Enemy/EnemySpawner.h"
#include "Archer/ArcherSpowner.h"
#include "Boss/BossSpawn.h"
//#include "Manual.h"
/// <summary>
/// �Q�[���N���X
/// </summary>
class Game final : public IGameObject
{
public:

	/// <summary>
	/// �X�e�[�W�N���X�ɓn���t�@�C���p�X
	/// L"Assets/level/"�͂���Ȃ�
	/// </summary>
	/// <param name="filePath"></param>
	void SetLevelFilePath(wchar_t* filePath) {
		wchar_t fileName[256] = L"Assets/level/";
		wcscat(fileName, filePath);
		wcscpy(m_LevelFilePath, fileName);
	}

	/// <summary>
	/// �v���C���[��Hp���擾����
	/// �X�e�[�W�̐؂�ւ����Ɏg�p����
	/// </summary>
	/// <returns></returns>
	const int GetPlayerHp() const {
		return m_Player->GetHp();
	}
	/// <summary>
	/// Hp�������p��
	/// �X�e�[�W�̐؂�ւ����Ɏg�p����
	/// </summary>
	/// <param name="hp">�v���C���[��Hp</param>
	void SetPlayerHp(const int hp) {
		m_SpownHp = hp;
	}
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
	Player* m_Player = nullptr;					//�v���C���[�̃|�C���^
	Stage* m_Stage = nullptr;					//�X�e�[�W�̃|�C���^
	GameCamera* m_Camera = nullptr;				//�J�����̃|�C���^
	wchar_t m_LevelFilePath[256] = {};			//�X�e�[�W�Ŏg���t�@�C���p�X��ۑ����镶����
	int m_SpownHp = 62.5f;						//�v���C���[��Hp
	EnemySpawner* m_EnemySpawner = nullptr;		//�X�P���g���̐e�N���X
	ArcherSpowner* m_ArcherSpawner = nullptr;	//�A�[�`���[�̐e�N���X
	BossSpawn* m_BossSpawner = nullptr;			//�{�X�̐e�N���X
	SoundSource m_BGM;							//�Q�[����BGM
	DirectionLight* m_Direction = nullptr;		//���z�Ɍ��������郉�C�g
};