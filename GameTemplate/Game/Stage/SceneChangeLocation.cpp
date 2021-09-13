#include "pch.h"
#include "SceneChangeLocation.h"
#include "Player/Player.h"
#include "Game.h"
#include "Fade.h"

namespace {
	const float Eria = 300.0f;	//�G���`�F���ł���͈�
}

bool SceneChangeLocation::Start()
{
	m_player = FindGO<Player>("player");
#ifdef _DEBUG
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"DebugShere.cmo");
	m_Skin->SetPosition(m_Pos);
	m_Skin->SetScale({ Eria,Eria,0.0f });
#endif
	return true;
}

void SceneChangeLocation::Update()
{
	//�����t�F�[�h������Ă��Ȃ��Ȃ�
	if (m_Fade == nullptr) {
		//�v���C���[�Ƃ̋����𑪂�
		CVector3 Diff = m_player->GetPosition() - m_Pos;
		Diff.y = 0.0f;
		//�����v���C���[���͈͂ɓ����Ă����
		if (Diff.Length() < Eria) {
			////�}�j���A����A�{�^���������Ă��炦��悤����
			//m_manual->SetManualPattern(Manual::ManualPattern::EriaChenge);
			//B�{�^���������ꂽ��
			if (g_pad[0].IsPress(enButtonA)) {
				//�t�F�[�h���o��
				m_Fade = NewGO<Fade>(0, "fade");
			}
		}
	}
	else {
		//�����t�F�[�h�̓����x��1.0�ȏ�Ȃ�
		if (m_Fade->GetAlpha() > 1.0f) {
			if (wcscmp(m_FilePath, L"Assets/level/StageLevel.tkl") == 0||
				wcscmp(m_FilePath, L"Assets/level/ReturnStageLevel.tkl") == 0) {
				Game* game = FindGO<Game>("game");
				float PlayerHP = game->GetPlayerHp();
				DeleteGO(game);
				game = nullptr;
				game = NewGO<Game>(0, "game");
				game->SetPlayerHp(PlayerHP);
				game->SetLevelFilePath(L"Bridge.tkl");
				DeleteGO(this);
			};
			if (wcscmp(m_FilePath, L"Assets/level/Bridge.tkl") == 0) {
				Game* game = FindGO<Game>("game");
				float PlayerHP = game->GetPlayerHp();
				DeleteGO(game);
				game = nullptr;
				game = NewGO<Game>(0, "game");
				game->SetPlayerHp(PlayerHP);
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
