#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class AttackState :	public IPlayerState
{
public:
	AttackState(Player* pl) :
		IPlayerState(pl) {

	}
	~AttackState() {};
	/// <summary>
	/// ‰ñ“]‚Å‚«‚é‚©
	/// </summary>
	/// <returns></returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
private:
	void Update()override;
};

