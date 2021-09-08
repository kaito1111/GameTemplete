#pragma once
#include "Player/State/IPlayerState.h"
#include "Player/DieSprite.h"
class ReSetGame;
class Fade;
/// <summary>
/// 死んだときに呼ばれるクラス
/// 継承を使って使用する
/// </summary>
class DieState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	DieState(Player* player)
		:IPlayerState(player) {
	};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override final;
};

