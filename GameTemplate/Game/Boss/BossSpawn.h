#pragma once
#include "Level/Level.h"
class BossSpawn : public IGameObject
{
public: 
	~BossSpawn() {};//デストラクタ

	bool Start()override;//初期化位置
	void OnDestroy()override;

	//levelデータを読みこむ
	void SetFilePath(wchar_t* fileName) {
		wcscpy(m_FilePath, fileName);
	}

private:
	wchar_t m_FilePath[256];//レベルのファイルパス
	Level m_Level;//レベル　

};

