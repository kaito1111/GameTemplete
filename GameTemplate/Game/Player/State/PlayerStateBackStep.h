#pragma once

#include "Player/State/IPlayerState.h"
class PlayerStateBackStep : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerStateBackStep(Player* pl) :
		IPlayerState(pl)
	{

	}
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update() override;
};

