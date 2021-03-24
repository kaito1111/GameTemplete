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
			//敵のインスタンスを作成
			Arrow* arrow = NewGO<Arrow>(0, "archer");
			//敵の初期位置を設定
			CVector3 SpownPos = funclevel.position;
			arrow->Init(SpownPos, funclevel.rotation);
			//archer->SetSpownPosition(SpownPos);
			////敵の初期回転量を設定
			//archer->SetRotation(funclevel.rotation);
			//リストに積む
			//m_EnemyList.push_back(enemy);
			CVector3 Pos = CVector3::Zero();
			Pos.x += 100.0f;
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
			//敵の初期位置を設定
			/*CVector3 */SpownPos = funclevel.position + Pos;
			enemy->SetSpownPos(SpownPos);
			//敵の初期回転量を設定
			enemy->SetRotation(funclevel.rotation);
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
