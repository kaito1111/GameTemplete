#pragma once

#include "Player/State/IPlayerState.h"

/// <summary>
/// 待機ステートクラス。
/// </summary>
class IdleState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	IdleState(Player* pl) :
		IPlayerState(pl)
	{

	}
	/// <summary>
	/// 更新処理。
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

