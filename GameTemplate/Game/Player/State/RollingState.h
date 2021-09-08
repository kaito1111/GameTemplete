#pragma once

#include "Player/State/IPlayerState.h"
/// <summary>
/// プレイヤーがステップするたびに呼ばれるクラス
/// 継承を使って利用する
/// </summary>
class RollingState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	RollingState(Player* pl) :
		IPlayerState(pl)
	{

	}
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update() override;
	/// <summary>
	///	回転できるかどうか
	/// </summary>
	/// <returns>バックステップ中にも回転ができる様にするのでtrueを返す</returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

