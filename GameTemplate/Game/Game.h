#pragma once

#include "Player/Player.h"
class Stage;
class GameCamera;
class Enemy;

class Game : public IGameObject
{
public:
	Game();
	~Game();

	void SetLevelFilePath(wchar_t* filePath) {
		wcscpy(m_LevelFilePath, filePath);
	}

	int GetPlayerHp() {
		return m_Player->GetHp();
	}
	void SetPlayerHp(int hp) {
		m_SpownHp = hp;
	}
private:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;
private:
	Player* m_Player = nullptr;
	Stage* m_Stage = nullptr;
	GameCamera* m_Camera = nullptr;
	Enemy* m_Enemy = nullptr;
	SpriteRender* m_Sprite;
	wchar_t m_LevelFilePath[256] = {};
	int m_SpownHp = 62.5;
};