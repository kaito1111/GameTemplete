#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class PlayerStateAttack :	public IPlayerState
{
public:
	PlayerStateAttack(Player* pl) :
		IPlayerState(pl) {

	}
private:
	void Update()override;
};

