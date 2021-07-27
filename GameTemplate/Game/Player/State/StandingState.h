#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class GameStart;
class StandingState : public IPlayerState
{
public:
	StandingState(Player* pl) :IPlayerState(pl) {

	}
	~StandingState()
	{

	}
	void Update()override;
private:
	GameStart* m_GameStart = nullptr;
};

