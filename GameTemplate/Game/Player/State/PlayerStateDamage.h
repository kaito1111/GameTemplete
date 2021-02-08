#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class PlayerStateDamage : public IPlayerState
{
public:
	PlayerStateDamage(Player* pl) :
		IPlayerState(pl) {};
	~PlayerStateDamage() {};
private:
	void Update()override;
};

