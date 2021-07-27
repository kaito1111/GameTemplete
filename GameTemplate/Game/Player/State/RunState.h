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
private:
	SoundSource m_sound;
};

