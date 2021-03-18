#include "pch.h"
#include "EnemySpawner.h"

bool EnemySpawner::Start()
{
	m_Level.Init(m_filePath, [&](LevelObjectData funclevel)->bool {
		if (wcscmp(funclevel.name, L"keleton") == 0) {
			//いったんここでエネミーを出す
			//あとからレベルごと分けて処理を分解する
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
			enemy->SetSpownPos(funclevel.position);
			enemy->SetRotation(funclevel.rotation);
			m_EnemyList.push_back(enemy);
			return true;
		}
	});
	return true;
}
void EnemySpawner::OnDestroy()
{
	for (Enemy* it : m_EnemyList) {
		DeleteGO(it);
	}
}
