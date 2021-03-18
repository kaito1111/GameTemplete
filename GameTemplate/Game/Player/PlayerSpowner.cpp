#include "pch.h"
#include "PlayerSpowner.h"

bool PlayerSpowner::Start()
{
	m_level.Init(m_filePath, [&](LevelObjectData funcLevel)->bool{
		if (wcscmp(L"Player", funcLevel.name) == 0) {
			m_player = NewGO<Player>(0);
			m_player->SetSpownPos(funcLevel.position);
			m_player->SetRotation(funcLevel.rotation);
		}
		return true;
	});
	return true;
}
