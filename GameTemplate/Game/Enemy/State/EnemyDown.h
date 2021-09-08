#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
/// <summary>
/// スケルトンが死ぬと呼ばれるクラス
/// 継承を使って利用する
/// </summary>
class EnemyDown : public IEnemyState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IEnemyStateにエネミーのポインタを確保している
	/// </summary>
	/// <param name="en">エネミーのポインタ</param>
	EnemyDown(Enemy* en) :
		IEnemyState(en) {};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update();
	/// <summary>
	/// Hpを減少させられるかどうか
	/// 死んでいるのでこれ以上Hpは減少させない
	/// </summary>
	/// <returns>死んでいるのでfalseを返す</returns>
	bool IsPossibleHpDown() {
		return false;
	}
};

