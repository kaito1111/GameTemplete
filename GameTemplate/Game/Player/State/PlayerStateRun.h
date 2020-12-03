#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class PlayerStateRun : public IPlayerState
{
public: 
	PlayerStateRun(Player* pl) :
		IPlayerState(pl) {

	}
	
	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update()override;

	/// <summary>
	/// 回転できるか
	/// </summary>
	/// <returns></returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

