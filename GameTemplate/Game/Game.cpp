#include "pch.h"
#include "Game.h"

#include "Player/Player.h"
#include "Stage/Stage.h"
#include "GameCamera.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	m_Stage = NewGO<Stage>(0);
	m_Stage->Load(m_LevelFilePath);
	m_Player = NewGO<Player>(1, "player");
	m_Player->SetSpownPos(m_Stage->GetPlayerPos());
	m_Player->SetRotation(m_Stage->GetPlayerRotation());
	m_Player->SetSpwonHp(m_SpownHp);
	m_Camera = NewGO<GameCamera>(0);
	m_Camera->SetStartAngle(m_Player->GetRot());
	m_EnemySpawner = NewGO<EnemySpawner>(0);
	m_EnemySpawner->SetFilePath(m_LevelFilePath);
	m_ArcherSpawner = NewGO<ArcherSpowner>(0);
	m_ArcherSpawner->SetFilePath(m_LevelFilePath);
	m_BossSpawner = NewGO<BossSpawn>(0);
	m_BossSpawner->SetFilePath(m_LevelFilePath);
	return true;
}

void Game::Update()
{
}

void Game::OnDestroy()
{
	DeleteGO(m_Player);
	DeleteGO(m_Stage);
	DeleteGO(m_Camera);
	DeleteGO(m_EnemySpawner);
	DeleteGO(m_ArcherSpawner);
	DeleteGO(m_BossSpawner);
}
