#pragma once

#include "Player/State/IPlayerState.h"

/// <summary>
/// �ҋ@�X�e�[�g�N���X�B
/// </summary>
class PlayerStateIdle : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerStateIdle(Player* pl) :
		IPlayerState(pl)
	{

	}
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �ړ����邩����B
	/// </summary>
	/// <returns></returns>
	bool IsPossibleMove() const override
	{
		return false;
	}

};

