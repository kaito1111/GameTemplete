#include "pch.h"
#include "SceneChangeLocation.h"
#include "Player/Player.h"
#include "Game.h"
#include "Fade.h"

bool SceneChangeLocation::Start()
{
	m_player = FindGO<Player>("player");
#ifdef _DEBUG
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"DebugShere.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetScale({ m_Eria,m_Eria,0.0f });
#endif
	return true;
}

void SceneChangeLocation::Update()
{
	//�����t�F�[�h������Ă��Ȃ��Ȃ�
	if (m_Fade == nullptr) {
		CVector3 Diff = m_player->GetPosition() - m_Pos;
		Diff.y = 0.0f;
		//�����v���C���[���͈͂ɓ����Ă����
		if (Diff.Length() < m_Eria) {
			//�t�F�[�h���o��
			m_Fade = NewGO<Fade>(0, "fade");
		}
	}
	else {
		//�����t�F�[�h�̓����x��1.0�ȏ�Ȃ�
		if (m_Fade->GetAlpha() > 1.0f) {
			if (wcscmp(m_FilePath, L"Assets/level/StageLevel.tkl") == 0||
				wcscmp(m_FilePath, L"Assets/level/ReturnStageLevel.tkl") == 0) {
				Game* game = FindGO<Game>("game");
				int PlayerHP = game->GetPlayerHp();
				DeleteGO(game);
				game = nullptr;
				game = NewGO<Game>(0, "game");
				game->SetPlayerHp(PlayerHP);
				game->SetLevelFilePath(L"Bridge.tkl");
				game->SetUpdateFlag( false);
				DeleteGO(this);
			};
			if (wcscmp(m_FilePath, L"Assets/level/Bridge.tkl") == 0) {
				Game* game = FindGO<Game>("game");
				DeleteGO(game);
				game = nullptr;
				game = NewGO<Game>(0, "game");
				game->SetLevelFilePath(L"StageBoss.tkl");
				DeleteGO(this);
			};
		}
	}
}

void SceneChangeLocation::OnDestroy()
{
#ifdef _DEBUG
	DeleteGO(m_Skin);
#endif
}
