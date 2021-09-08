#pragma once
#include "Player/State/IPlayerState.h"
class Player;
/// <summary>
/// プレイヤーが攻撃するたびに呼ばれるクラス
/// 継承を使って利用する
/// </summary>
class AttackState :	public IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// 何も書いてないが、IPlayerStateにプレイヤーポインタを確保している
	/// </summary>
	/// <param name="pl">プレイヤーポインタ</param>
	AttackState(Player* pl) :
		IPlayerState(pl) {

	}
	~AttackState() {};
private:
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
	/// <summary>
	///	回転できるかどうか
	/// </summary>
	/// <returns>攻撃中は回転ができるのでtrueを返す</returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

