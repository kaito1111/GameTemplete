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
	//�X�e�[�W���o��
	m_Stage = NewGO<Stage>(0);
	m_Stage->Load(m_LevelFilePath);
	//�����ăv���C���[���o��
	m_Player = NewGO<Player>(1, "player");
	m_Player->SetSpownPos(m_Stage->GetPlayerPos());
	m_Player->SetRotation(m_Stage->GetPlayerRotation());
	m_Player->SetSpwonHp(m_SpownHp);
	m_Player->SetIdleState();
	//�J����
	m_Camera = NewGO<GameCamera>(2);
	m_Camera->SetStartAngle(m_Player->GetRot());
	//�X�P���g��
	m_EnemySpawner = NewGO<EnemySpawner>(0);
	m_EnemySpawner->SetFilePath(m_LevelFilePath);
	//�|��
	m_ArcherSpawner = NewGO<ArcherSpowner>(0);
	m_ArcherSpawner->SetFilePath(m_LevelFilePath);
	//�{�X
	m_BossSpawner = NewGO<BossSpawn>(0);
	m_BossSpawner->SetFilePath(m_LevelFilePath);
	//BGM�𗬂�
	m_BGM.Init(L"bgm.wav");
	m_BGM.Play(true);
	////�}�j���A�������
	//m_Manual = NewGO<Manual>(0, "manual");
	//�f�B���N�V�������C�g�����
	m_Direction = NewGO< DirectionLight>(0, "direction");
	CVector3 Dir = CVector3::One();
	Dir = { 2.0,-1.0f,2.0f };
	Dir.Normalize();
	CVector3 color = CVector3::One()*0.5f;
	m_Direction->SetColor(color);
	m_Direction->SetDirection(Dir);
	m_Direction->SetEyePos(g_camera3D.GetPosition());
	m_Direction->SetSpecPow(5.0f);
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
	DeleteGO(m_Direction);
	//DeleteGO(m_Manual);
}
