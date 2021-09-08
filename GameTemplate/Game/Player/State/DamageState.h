#pragma once
#include "Player/State/IPlayerState.h"
class Player;
/// <summary>
///プレイヤーがダメージを受けると呼ばれるクラス
/// 継承を使って使用する
/// </summary>
class DamageState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	DamageState(Player* pl) :
		IPlayerState(pl) {};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
};