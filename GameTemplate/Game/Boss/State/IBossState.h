#pragma once
#include "Boss/Boss.h"
/// <summary>
/// ボスのステートパターンのインターフェースクラス
/// </summary>
class IBossState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IBossStateにボスのポインタを確保している
	/// </summary>
	/// <param name="boss">ボスのポインタ</param>
	IBossState(Boss* boss)
		: m_Boss(boss) 
	{};

	/// <summary>
	/// インスタンスが生成されると、一度だけ呼ばれる仮想開始処理
	/// </summary>
	virtual void Start() {};
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// 更新関数を使わない事は大体ないので、
	/// 純粋化して、絶対に呼ぶようにしている
	/// </summary>
	virtual void Update() = 0;


protected:
	Boss* m_Boss = nullptr;
};

