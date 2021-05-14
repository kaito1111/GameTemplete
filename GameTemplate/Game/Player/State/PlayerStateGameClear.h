#pragma once
#include "IPlayerState.h"
class HuntedSprite;
class PlayerStateGameClear : public IPlayerState
{
	HuntedSprite* m_HuntedSprite = nullptr;
public:
	PlayerStateGameClear(Player* pl) :
		IPlayerState(pl) {}
	~PlayerStateGameClear() {};
	void Update();
};

