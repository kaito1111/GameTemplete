#pragma once

#include "Player/State/IPlayerState.h"
class PlayerStateBackStep : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerStateBackStep(Player* pl) :
		IPlayerState(pl)
	{

	}
	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update() override;
};

