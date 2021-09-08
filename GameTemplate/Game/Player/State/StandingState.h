#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class GameStart;
/// <summary>
/// タイトル画面からゲーム画面に移行する時の状態
/// 継承を使って使用する
/// </summary>
class StandingState : public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	StandingState(Player* pl) :IPlayerState(pl) {

	}
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
	GameStart* m_GameStart = nullptr;		//ゲームシーンに遷移するクラスのポインタ
};

