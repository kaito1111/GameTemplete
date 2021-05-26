#include "pch.h"
#include "BossSpawn.h"
#include "Boss.h"

bool BossSpawn::Start() {
	m_Level.Init(m_FilePath, [&](LevelObjectData funclevel)->bool {
		if (wcscmp(L"Boss", funclevel.name) == 0) {
			Boss* boss = NewGO<Boss>(0, "Boss");
			boss->SetSpownPos(funclevel.position);
			boss->SetRotation(funclevel.rotation);
		}
		return true;
	});
	return true;
}

void BossSpawn::OnDestroy()
{
	DeleteGOs("Boss");
}
