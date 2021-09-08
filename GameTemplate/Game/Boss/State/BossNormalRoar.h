#pragma once
#include "IBossState.h"
/// <summary>
/// ボスが咆哮をするときに呼ばれるクラス
/// 継承を使って利用する
/// </summary>
class BossNormalRoar:public IBossState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IBossStateにボスのポインタを確保している
	/// </summary>
	/// <param name="boss">ボスのポインタ</param>
	BossNormalRoar(Boss* boss) :
		IBossState(boss) {
	};

	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;

private:
};

