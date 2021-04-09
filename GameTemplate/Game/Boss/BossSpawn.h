#pragma once
#include "Level/Level.h"
class BossSpawn : public IGameObject
{
public: 
	~BossSpawn() {};

	bool Start()override;

	void SetFilePath(wchar_t* fileName) {
		wcscpy(m_FilePath, fileName);
	}

private:
	wchar_t m_FilePath[256];
	Level m_Level;

};

