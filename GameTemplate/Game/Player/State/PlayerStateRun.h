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
	/// XVˆ—B
	/// </summary>
	void Update()override;

	/// <summary>
	/// ‰ñ“]‚Å‚«‚é‚©
	/// </summary>
	/// <returns></returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

