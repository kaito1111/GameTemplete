#pragma once
#include "IBossState.h"
/// <summary>
/// ボスが攻撃をする時に呼ぶクラス
/// 継承を使って利用する
/// </summary>
class BossAttackState : public IBossState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IBossStateにボスのポインタを確保している
	/// </summary>
	/// <param name="boss">ボスのポインタ</param>
	BossAttackState(Boss* boss) :
		IBossState(boss) {};
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
};

