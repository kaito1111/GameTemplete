#pragma once
#include "Player/State/IPlayerState.h"
#include "Player/DieSprite.h"
class ReSetGame;
class Fade;
class DieState : public IPlayerState
{
public:
	DieState(Player* player)
		:IPlayerState(player) {
		m_DieSprite = NewGO< DieSprite>(0);
	};
	~DieState();

	void Update()override final;
	void Delete()override final;

private:
	void ReStart();
	DieSprite* m_DieSprite = nullptr;
	int m_Rezult = 0; 
	ReSetGame* m_resetGame = nullptr;
};

