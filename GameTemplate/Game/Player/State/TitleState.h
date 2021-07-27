#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class TitleState : public IPlayerState
{
public:
	TitleState(Player* pl) :IPlayerState (pl){};
	~TitleState() {};

	void Update()override;


};

