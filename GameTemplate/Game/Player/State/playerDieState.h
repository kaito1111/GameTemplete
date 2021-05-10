#pragma once
#include "Player/State/IPlayerState.h"
#include "Player/DieSprite.h"
class Fade;
class PlayerDieState : public IPlayerState
{
public:
	PlayerDieState(Player* player)
		:IPlayerState(player) {
		m_DieSprite = NewGO< DieSprite>(0);
	};
	~PlayerDieState();

	void Update()override;
private:
	void ReStart();
	DieSprite* m_DieSprite = nullptr;
	Fade* m_fade = nullptr;
	int m_Rezult = 0;
};

