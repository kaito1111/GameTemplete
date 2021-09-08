#pragma once
#include "Archer/Archer.h"

/// <summary>
/// アーチャーが待機状態に呼ばれる関数
/// 継承を使って利用する
/// </summary>
class ArcherIdleState : public IArcherState
{
public:
	/// <summary>
	/// コンストラクタ
	/// IArcherStateにArcherのポインタを渡している
	/// </summary>
	/// <param name="a">アーチャーポインタ</param>
	ArcherIdleState(Archer* a) :
		IArcherState(a){}
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
};

