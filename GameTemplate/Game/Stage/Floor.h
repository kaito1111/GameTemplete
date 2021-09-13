#pragma once
/// <summary>
/// 床
/// </summary>
class Floor final : public IGameObject
{
public:
	/// <summary>
	/// インスタンスが生成されると、一度だけ呼ばれる開始処理
	/// </summary>
	/// <remarks>
	/// UnityのStart()関数の仕様に準拠。
	/// </remarks>
	/// <returns>
	/// trueが帰ってきたら、初期化完了。
	/// 複数フレームにわたって初期化をしたい場合は、
	/// 初期化完了までfalseを返す。
	/// </returns>
	bool Start() override final;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update() override final;
	/// <summary>
	///	モデルの位置を設定
	/// </summary>
	/// <param name="pos">位置</param>
	void SetPosition(const CVector3& pos) {
		m_Pos = pos;
	}
	/// <summary>
	/// モデルの回転量を設定
	/// </summary>
	/// <param name="rot">回転量</param>
	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}

private:
	SkinModelRender* m_Model = nullptr;				//床のモデル
	CVector3 m_Pos = CVector3::Zero();				//モデルの位置
	CQuaternion m_Rot = CQuaternion::Identity();	//モデルの回転量
	CVector3 m_Scale = CVector3::One();				//モデルの大きさ
};