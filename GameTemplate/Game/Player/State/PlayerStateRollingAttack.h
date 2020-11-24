#pragma once
#include "PLayer/State/IPlayerState.h"
class Player;
class PlayerStateRollingAttack : public IPlayerState
{
public: 
	PlayerStateRollingAttack(Player* pl) :
		IPlayerState(pl)
	{

	}
private:
	void Update()override;
};

