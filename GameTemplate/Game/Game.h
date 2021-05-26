#pragma once

#include "Player/Player.h"
class Stage;
class GameCamera;
#include "Enemy/EnemySpawner.h"
#include "Archer/ArcherSpowner.h"
#include "Boss/BossSpawn.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();

	//L"Assets/level/"‚Í‚¢‚ç‚È‚¢
	void SetLevelFilePath(wchar_t* filePath) {
		wchar_t fileName[256] = L"Assets/level/";
		wcscat(fileName, filePath);
		wcscpy(m_LevelFilePath, fileName);
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
	wchar_t m_LevelFilePath[256] = {};
	int m_SpownHp = 62.5;
	EnemySpawner* m_EnemySpawner = nullptr;
	ArcherSpowner* m_ArcherSpawner = nullptr;
	BossSpawn* m_BossSpawner = nullptr;
	SkinModel model;
};