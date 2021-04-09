#include "pch.h"
#include "EnemySpawner.h"
#include "Archer/Archer.h"
#include "Archer/Arrow.h"

bool EnemySpawner::Start()
{
	//Gameクラスから持ってきたファイルパスをロード
	m_Level.Init(m_filePath, [&](LevelObjectData funclevel)->bool {
		//エネミーの名前が見つかったら
		if (wcscmp(funclevel.name, L"keleton") == 0) {
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
			//敵の初期位置を設定
			CVector3 SpownPos = funclevel.position;
			enemy->SetSpownPos(SpownPos);
			//敵の初期回転量を設定
			enemy->SetRotation(funclevel.rotation);
			//リストに積む
			m_EnemyList.push_back(enemy);
			return true;
		}
	});
	return true;
}
void EnemySpawner::OnDestroy()
{
	//敵のインスタンスを削除
	DeleteGOs("enemy");
}
