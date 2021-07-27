#pragma once
class Player;

/// <summary>
/// プレイヤーの状態の基底クラス。
/// </summary>
class IPlayerState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pl">プレイヤー</param>
	IPlayerState(Player* pl) :
		m_player(pl){}

	virtual ~IPlayerState(){}
	/// <summary>
	/// 更新処理。
	/// </summary>
	virtual void Update() = 0;
	virtual void Delete(){}
	/// <summary>
	/// 移動可能か判定する。
	/// </summary>
	virtual bool IsPossibleMove() const
	{
		return true;
	}
	/// <summary>
	/// 回転できるか判定する？
	/// </summary>
	/// <returns></returns>
	virtual bool IsPossibleRotate() const
	{
		return false;
	}
protected:
	Player* m_player = nullptr;	//プレイヤー。
};

