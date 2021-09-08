#pragma once
class Player;

/// <summary>
/// プレイヤーのステートパターンのインターフェースクラス
/// </summary>
class IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// プレイヤーのポインタをこの関数で確保する
	/// </summary>
	/// <param name="pl">プレイヤーのポインタ</param>
	IPlayerState(Player* pl) :
		m_player(pl){}

	virtual ~IPlayerState(){}
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// 更新関数を使わない事は大体ないので、
	/// 純粋化して、絶対に呼ぶようにしている
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 移動可能かどうかを返す仮想関数
	/// </summary>
	/// <returns>trueを返すと移動できる</returns>
	virtual bool IsPossibleMove() const
	{
		return true;
	}
	/// <summary>
	/// 回転可能かどうかを返す仮想関数
	/// </summary>
	/// <returns>trueを返すと回転できる</returns>
	virtual bool IsPossibleRotate() const
	{
		return false;
	}
protected:
	Player* m_player = nullptr;	//プレイヤーポインタ。
};

