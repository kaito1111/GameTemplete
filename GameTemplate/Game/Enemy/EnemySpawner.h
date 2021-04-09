#pragma once
#include "Enemy/Enemy.h"
#include "level/level.h"
class EnemySpawner : public IGameObject
{
public:
	EnemySpawner() {};
	~EnemySpawner() {};

	//敵の出てくるファイルパスをロード
	void SetFilePath(const wchar_t* fileName) {
		wcscpy_s(m_filePath, fileName);
	}

	//初期化
	bool Start()override;
	//消された瞬間に走る
	void OnDestroy()override;
private:
	Level m_Level;						//レベル
	std::vector<Enemy*> m_EnemyList;	//敵のリスト
	wchar_t m_filePath[256] = {};		//レベルをロードする用のファイルパス
};

