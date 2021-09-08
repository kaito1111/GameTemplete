#pragma once
#include "PLayer/State/IPlayerState.h"
class Player;
/// <summary>
/// ローリングアタックをすると呼ばれる関数
/// 継承を使って利用する
/// </summary>
class RollingAttackState : public IPlayerState
{
public: 
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	RollingAttackState(Player* pl) :
		IPlayerState(pl)
	{

	}
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
	/// <summary>
	/// <summary>
	///	回転できるかどうか
	/// </summary>
	/// <returns>攻撃中は回転ができるのでtrueを返す</returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

