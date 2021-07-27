#pragma once

#include "Player/State/IPlayerState.h"
class BackStepState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BackStepState(Player* pl) :
		IPlayerState(pl)
	{

	}
	~BackStepState()
	{

	}
	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update() override;
	/// <summary>
	/// 回転できるか
	/// </summary>
	/// <returns></returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

