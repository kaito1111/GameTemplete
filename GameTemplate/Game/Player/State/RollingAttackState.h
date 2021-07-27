#pragma once
#include "PLayer/State/IPlayerState.h"
class Player;
class RollingAttackState : public IPlayerState
{
public: 
	RollingAttackState(Player* pl) :
		IPlayerState(pl)
	{

	}
	/// <summary>
	/// ��]�ł��邩
	/// </summary>
	/// <returns></returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
private:
	void Update()override;
};

