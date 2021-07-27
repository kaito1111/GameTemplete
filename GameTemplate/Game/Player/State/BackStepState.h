#pragma once

#include "Player/State/IPlayerState.h"
class BackStepState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BackStepState(Player* pl) :
		IPlayerState(pl)
	{

	}
	~BackStepState()
	{

	}
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update() override;
	/// <summary>
	/// ��]�ł��邩
	/// </summary>
	/// <returns></returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

