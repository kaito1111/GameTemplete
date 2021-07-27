#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class RunState : public IPlayerState
{
public: 
	RunState(Player* pl) :
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
private:
	SoundSource m_sound;
};

