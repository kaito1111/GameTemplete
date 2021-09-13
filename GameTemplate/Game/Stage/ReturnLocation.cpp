#include "pch.h"
#include "ReturnLocation.h"
#include "Player/Player.h"
#include "Fade.h"
#include "Game.h"

namespace {
	const float Eria = 70.0f;	//エリアチェンジの範囲
}

bool ReturnLocatoin::Start()
{
	m_player = FindGO<Player>("player");
#ifdef _DEBUG
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"ReturnRoad.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetScale({ Eria,Eria,0.0f });
#endif
	return true;
}

void ReturnLocatoin::Update()
{
	CVector3 Diff = m_player->GetPosition() - m_Pos;
	Diff.y = 0.0f;
	if (Diff.Length() < Eria) {
		if (g_pad[0].IsPress(enButtonA)) {
			NewGO<Fade>(0, "fade");
			if (wcscmp(m_FilePath, L"Assets/level/Bridge.tkl") == 0) {
				Game* game = FindGO<Game>("game");
				float PlayerHP = game->GetPlayerHp();
				DeleteGO(game);
				game = nullptr;
				game = NewGO<Game>(0, "game");
				game->SetPlayerHp(PlayerHP);
				game->SetLevelFilePath(L"ReturnStageLevel.tkl");
				DeleteGO(this);
			}
		}
	}
}

void ReturnLocatoin::OnDestroy()
{
#ifdef _DEBUG
	DeleteGO(m_Skin);
#endif
}
