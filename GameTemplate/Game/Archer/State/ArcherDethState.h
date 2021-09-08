#pragma once
#include "Archer/State/IArcherState.h"
class Archer;
/// <summary>
/// アーチャーが死んだときに呼ばれる関数
/// 継承を使って利用する
/// </summary>
class ArcherDethState :
	public IArcherState
{
public :
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IArcherStateにアーチャーのポインタを確保している
	/// </summary>
	/// <param name="ac">アーチャーポインタ</param>
	ArcherDethState(Archer* ac) :
		IArcherState(ac) {

	}
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update() {};
	/// <summary>
	/// Hpを減少させられるかどうか
	/// 死んでいるのでこれ以上Hpは減少させない
	/// </summary>
	/// <returns>死んでいるのでfalseを返す</returns>
	bool IsPossibleHpDown() {
		return false;
	}
};

