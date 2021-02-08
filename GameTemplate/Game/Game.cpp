#include "pch.h"
#include "Game.h"

#include "Player/Player.h"
#include "Stage.h"
#include "GameCamera.h"
#include "Enemy/Enemy.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	m_Player = NewGO<Player>(1, "player");
	m_Camera = NewGO<GameCamera>(0);
	m_Camera->SetPlayer(m_Player);
	m_Stage = NewGO<Stage>(0);
	m_Enemy = NewGO<Enemy>(2,"enemy");
	m_Enemy->SetPlayer(m_Player);
	//m_Sprite = NewGO<SpriteRender>(0);
	//m_Sprite->Init(L"Assets/sprite/discode_icon.dds");
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
	DeleteGO(m_Enemy);
}
