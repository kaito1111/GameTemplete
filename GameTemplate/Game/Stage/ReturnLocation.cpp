#include "pch.h"
#include "ReturnLocation.h"
#include "Player/Player.h"
#include "Fade.h"
#include "Game.h"

bool ReturnLocatoin::Start()
{
	m_player = FindGO<Player>("player");
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"ReturnRoad.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetScale({ m_Eria,m_Eria,0.0f });
	return true;
}

void ReturnLocatoin::Update()
{
	CVector3 Diff = m_player->GetPosition() - m_Pos;
	Diff.y = 0.0f;
	if (Diff.Length() < m_Eria) {
		NewGO<Fade>(0, "fade");
		if (wcscmp(m_FilePath, L"Assets/level/Bridge.tkl") == 0) {
			Game* game = FindGO<Game>("game");
			DeleteGO(game);
			game = nullptr;
			game = NewGO<Game>(0, "game");
			game->SetLevelFilePath(L"StageLevel.tkl");
			DeleteGO(this);
		};
		if (wcscmp(m_FilePath, L"Assets/level/Stage2Level.tkl") == 0) {
			Game* game = FindGO<Game>("game");
			DeleteGO(game);
			game = nullptr;
			game = NewGO<Game>(0, "game");
			game->SetLevelFilePath(L"Bridge.tkl");
			DeleteGO(this);
		};
	}
}

void ReturnLocatoin::OnDestroy()
{
	DeleteGO(m_Skin);
}
