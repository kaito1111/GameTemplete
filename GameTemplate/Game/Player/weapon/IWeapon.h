#pragma once
/// <summary>
/// 武器となるクラスに継承する基底クラス
/// このクラスで向きの切り替えをする（未実装）
/// 
/// </summary>
class IWeapon
{
public:
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual	~IWeapon() {};

	/// <summary>
	/// インスタンスが呼ばれると一度だけ呼ばれる純粋仮想関数。
	/// 初期化関数を使わない事は大体ないので、
	/// 純粋化して、絶対に呼ぶようにしている
	/// </summary>
	virtual void Start() = 0;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// 更新関数を使わない事は大体ないので、
	/// 純粋化して、絶対に呼ぶようにしている
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// インスタンスが破棄されると一度だけ呼ばれる純粋仮想関数。
	/// 破棄関数を使わない事は大体ないので、
	/// 純粋化して、絶対に呼ぶようにしている
	/// </summary>
	virtual void Delete() = 0;
	/// <summary>
	/// 武器の位置を設定する
	/// </summary>
	/// <param name="pos">武器の位置</param>
	void SetPosition(CVector3 pos) {
		m_Position = pos;
	}
	/// <summary>
	/// 武器の回転を設定する
	/// </summary>
	/// <param name="rot">武器の回転</param>
	void SetRotation(CQuaternion rot) {
		m_Rotation = rot;
	}
	/// <summary>
	/// モデルを取得するイ
	/// </summary>
	/// <returns>モデル</returns>
	SkinModelRender* GetModel() {
		return m_model;
	}
protected:
	CVector3 m_Position = CVector3::Zero();				//武器モデルの位置
	CQuaternion m_Rotation = CQuaternion::Identity();	//武器モデルの回転
	SkinModelRender* m_model = nullptr;					//武器のモデル

};

