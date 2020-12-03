#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class PlayerStateRun : public IPlayerState
{
public: 
	PlayerStateRun(Player* pl) :
		IPlayerState(pl) {

	}
	
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update()override;

	/// <summary>
	/// ��]�ł��邩
	/// </summary>
	/// <returns></returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

