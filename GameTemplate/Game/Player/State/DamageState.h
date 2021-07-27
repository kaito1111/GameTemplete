#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class DamageState : public IPlayerState
{
public:
	DamageState(Player* pl) :
		IPlayerState(pl) {};
	~DamageState() {};
private:
	void Update()override;
};

