#pragma once
#include "Player/State/IPlayerState.h"
class Player;
/// <summary>
/// タイトル画面で待機しているときに呼ばれるクラス
/// 継承を使って利用する
/// </summary>
class TitleState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	TitleState(Player* pl) :IPlayerState (pl){};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
};

