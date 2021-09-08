#pragma once
class Enemy;
/// <summary>
/// スケルトンのステートパターンのインターフェースクラス
/// </summary>
class IEnemyState
{
public:
	/// <summary>
	/// コンストラクタ
	/// エネミーのポインタをこの関数で確保する
	/// </summary>
	/// <param name="en">エネミーのポインタ</param>
	IEnemyState(Enemy* en) :
		m_enemy(en) 
	{
	};
	/// <summary>
	///デストラクタの仮想関数
	/// </summary>
	virtual ~IEnemyState() {};
	/// <summary>
	/// 毎フレーム呼ばれる仮想更新処理。
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// HPを減少させられるかを返す関数
	/// </summary>
	/// <returns>trueを返すことで減少させることができる</returns>
	virtual bool IsPossibleHpDown() {
		return true;
	}
private:	
	/// <summary>
	/// 移動可能かどうかを返す関数
	/// </summary>
	/// <returns>trueで移動可能</returns>
	virtual bool IsPossibleMove() const {
		return true;
	}
	/// <summary>
	/// 回転可能かどうかを返す関数
	/// </summary>
	/// <returns>tureで回転可能</returns>
	virtual bool IsPossibleRotate()const {
		return true;
	}

protected:
	Enemy* m_enemy = nullptr;	//エネミーポインタ
};

