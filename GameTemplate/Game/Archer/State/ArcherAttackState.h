#pragma once
#include "IArcherState.h"
class Archer;
/// <summary>
/// アーチャーの攻撃状態を管理するクラス
/// 継承を使って利用する
/// </summary>
class ArcherAttackState : public IArcherState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IArcherStateにアーチャーのポインタを確保している
	/// </summary>
	/// <param name="a">アーチャーポインタ</param>
	ArcherAttackState(Archer* a) :
		IArcherState(a) {};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
};

