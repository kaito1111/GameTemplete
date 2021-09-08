#include "pch.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "Stage/Stage.h"
#include "Player/Player.h"
#include "GameCamera.h"
#include "CampFire.h"

bool Title::Start()
{
	m_TitleSprite = NewGO<SpriteRender>(0);
	m_TitleSprite->Init(L"TitleButton.dds");
	m_Stage = NewGO<Stage>(0);
	m_Stage->Load(L"Assets/level/Title.tkl");
	m_Player = NewGO<Player>(0,"player");
	m_Player->SetSpownPos(m_Stage->GetPlayerPos());
	m_Player->SetTitleState();

	g_camera3D.SetPosition(m_Stage->GetTitleCameraPos());
	g_camera3D.SetTarget(m_Stage->GetTitleCameraTarget());
	g_camera3D.Update();
	m_camp = NewGO<CampFire>(0,"campFire");
	return true;
}

void Title::Update()
{
	if (g_pad[0].IsPressAnyKey()) {
		m_AlphaAdd = 0.1f;
		m_Player->SetStandingState();
	}
	float lightPow = m_camp->GetLightPow() / m_camp->GetMaxLightPow();
	m_Alpha = lightPow;
	m_TitleSprite->SetAlpha(m_Alpha);
	g_camera3D.Update();
}

void Title::OnDestroy()
{
	DeleteGO(m_TitleSprite);
	DeleteGO(m_Player);
	DeleteGO(m_Stage);
	DeleteGO(m_camera);
	DeleteGO(m_camp);
}
