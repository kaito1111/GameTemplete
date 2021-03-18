#pragma once
#include "Enemy/Enemy.h"
#include "level/level.h"
class EnemySpawner : public IGameObject
{
public:
	EnemySpawner() {};
	~EnemySpawner() {};

	//�G�̏o�Ă���t�@�C���p�X�����[�h
	void SetFilePath(wchar_t* fileName) {
		wcscpy_s(m_filePath, fileName);
	}

	bool Start();
	void OnDestroy();
private:
	Level m_Level;
	std::vector<Enemy*> m_EnemyList;
	wchar_t m_filePath[256] = {};
};

