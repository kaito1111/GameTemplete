#pragma once
class Archer;
/// <summary>
/// アーチャーのステートパターンのインターフェースクラス
/// </summary>
class IArcherState
{
public:
	/// <summary>
	/// コンストラクタ
	/// アーチャーポインタをこの関数で確保する
	/// </summary>
	/// <param name="a">アーチャーポインタ</param>
	IArcherState(Archer* a):
	m_Archer(a){};
	/// <summary>
	///デストラクタの仮想関数
	/// </summary>
	virtual ~IArcherState() {};
	/// <summary>
	/// インスタンスが生成されると、一度だけ呼ばれる仮想開始処理
	/// </summary>
	virtual void Start();
	/// <summary>
	/// 毎フレーム呼ばれる仮想更新処理。
	/// </summary>
	virtual void Update();
	/// <summary>
	/// HPを減少させられるかを返す関数
	/// </summary>
	/// <returns>trueを返すことで減少させることができる</returns>
	virtual bool IsPossibleHpDown() {
		return true;
	};
protected:
	Archer* m_Archer = nullptr;
};

