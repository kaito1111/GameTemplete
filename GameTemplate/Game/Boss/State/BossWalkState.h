#pragma once
#include "IBossState.h"
/// <summary>
/// ボスが歩く時に呼ぶクラス
/// 継承を使って利用する
/// </summary>
class BossWalkState : public IBossState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IBossStateにボスのポインタを確保している
	/// </summary>
	/// <param name="boss">ボスのポインタ</param>
	BossWalkState(Boss* boss) :
		IBossState(boss) {};

	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
};

