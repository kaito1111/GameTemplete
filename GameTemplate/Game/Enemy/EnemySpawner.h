#pragma once
#include "Enemy/Enemy.h"
#include "level/level.h"
class EnemySpawner : public IGameObject
{
public:
	EnemySpawner() {};
	~EnemySpawner() {};

	//�G�̏o�Ă���t�@�C���p�X�����[�h
	void SetFilePath(const wchar_t* fileName) {
		wcscpy_s(m_filePath, fileName);
	}

	//������
	bool Start()override;
	//�����ꂽ�u�Ԃɑ���
	void OnDestroy()override;
private:
	Level m_Level;						//���x��
	std::vector<Enemy*> m_EnemyList;	//�G�̃��X�g
	wchar_t m_filePath[256] = {};		//���x�������[�h����p�̃t�@�C���p�X
};

