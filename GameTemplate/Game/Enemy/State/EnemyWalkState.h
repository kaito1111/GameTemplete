#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
/// <summary>
/// スケルトンが歩く時に呼ばれるクラス
/// 継承を使って利用する
/// </summary>
class EnemyWalkState : public IEnemyState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IEnemyStateにエネミーのポインタを確保している
	/// </summary>
	/// <param name="en">エネミーのポインタ</param>
	EnemyWalkState(Enemy* en) :
		IEnemyState(en) {};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update() override;
};

