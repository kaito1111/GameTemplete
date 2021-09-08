#pragma once

#include "Player/State/IPlayerState.h"

/// <summary>
/// プレイヤーが何もしていないときに呼ばれる待機クラス。
/// 継承を使って使用する
/// </summary>
class IdleState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	IdleState(Player* pl) :
		IPlayerState(pl)
	{

	}
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update() override;
	/// <summary>
	/// 移動するか判定。
	/// </summary>
	/// <returns></returns>
	bool IsPossibleMove() const override
	{
		return false;
	}
};

