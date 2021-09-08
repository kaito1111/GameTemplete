#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
/// <summary>
/// スケルトンが攻撃を受けると呼ばれるクラス
/// 継承を使って利用する
/// </summary>
class EnemyDamageState : public IEnemyState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IEnemyStateにエネミーのポインタを確保している
	/// </summary>
	/// <param name="en">エネミーのポインタ</param>
	EnemyDamageState(Enemy* en) :
		IEnemyState(en) {};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
};

