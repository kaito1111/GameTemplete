#pragma once
#include "IBossState.h"
/// <summary>
/// ボスの登場時に一度だけ呼ばれる関数
/// 咆哮アニメーションを流す
/// 継承を使って利用する
/// </summary>
class BossAppearanceRoarState : public IBossState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IBossStateにボスのポインタを確保している
	/// </summary>
	/// <param name="boss">ボスのポインタ</param>
	BossAppearanceRoarState(Boss* boss) :
		IBossState(boss) {
	};
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;

private:
 };

