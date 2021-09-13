#pragma once
class Candle: public IGameObject
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
	bool Start()override final;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override final;
	/// <summary>
	/// インスタンスが破棄される時に呼ばれる関数。
	/// </summary>
	/// <remarks>
	/// 本エンジンで実装している、ゲームオブジェクトを削除する
	/// DeleteGO関数は、すぐにインスタンスを削除するわけではなく、
	/// 1フレーム遅れてインスタンスが削除される。
	/// そのため、デストラクタの呼び出しが、DeleteGOの呼び出しから1フレーム遅れることとなる。
	/// DeleteGOが呼ばれたタイミングで、行いたい終了処理はOnDestroy()に記述する。
	/// </remarks>
	void OnDestroy()override final;

	/// <summary>
	/// モデル位置を設定
	/// </summary>
	/// <param name="pos">モデルの位置</param>
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	/// <summary>
	/// モデルの回転を設定
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot) {
		m_Rotation = rot;
	}
private:
	SkinModelRender* m_Model = nullptr;					//キャンドルのモデル
	CVector3 m_Position = CVector3::Zero();				//位置
	CQuaternion m_Rotation = CQuaternion::Identity();	//回転
	PointLight* m_PointLightRed = nullptr;				//赤色の光源
	float m_LightPower = 200.0f;						//光の強さ
	float m_LightMulPower = -8.0f;						//光の増減を管理する変数
	CVector3 LightPos = CVector3::Zero();				//光の位置
	PointLight* m_PointLightYellow = nullptr;			//黄色の光源
	Effect* m_Effect = nullptr;							//炎のエフェクト
};