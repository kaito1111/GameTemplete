#pragma once

#include "Player/Player.h"
class Stage;
class GameCamera;
#include "Enemy/EnemySpawner.h"
#include "Archer/ArcherSpowner.h"
#include "Boss/BossSpawn.h"
//#include "Manual.h"

class Game final : public IGameObject
{
public:
	Game();
	~Game();

	//L"Assets/level/"はいらない
	void SetLevelFilePath(wchar_t* filePath) {
		wchar_t fileName[256] = L"Assets/level/";
		wcscat(fileName, filePath);
		wcscpy(m_LevelFilePath, fileName);
	}

	//level上で設置されていたプレイヤーの位置を返す
	int GetPlayerHp() {
		return m_Player->GetHp();
	}
	//Hpを引き継ぐ
	void SetPlayerHp(int hp) {
		m_SpownHp = hp;
	}
private:
	//初期化
	bool Start()override final;
	//更新
	void Update()override final;
	//削除
	void OnDestroy()override final;
private:
	Player* m_Player = nullptr;
	Stage* m_Stage = nullptr;
	GameCamera* m_Camera = nullptr;
	wchar_t m_LevelFilePath[256] = {};
	int m_SpownHp = 62.5f;
	EnemySpawner* m_EnemySpawner = nullptr;
	ArcherSpowner* m_ArcherSpawner = nullptr;
	BossSpawn* m_BossSpawner = nullptr;
	SkinModel model;
	SoundSource m_BGM;
	DirectionLight* m_Direction = nullptr;
	//Manual* m_Manual = nullptr;
};