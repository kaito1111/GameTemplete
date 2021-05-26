#pragma once
#include "Player/Player.h"
#include "level/Level.h"
class PlayerSpowner : public IGameObject
{
public:
	~PlayerSpowner() {};
	 
	//レベルでロードするファイルパスをGameクラスで設定
	void SetFilePath(wchar_t* fileName) {
		wcscpy_s(m_filePath, fileName);
	}

	bool Start()override;
	void OnDestroy()override;

private:
	Player* m_player = nullptr;		//プレイヤー
	Level m_level;					//レベル
	wchar_t m_filePath[256] = {};	//レベルでロードするファイルパス
};

