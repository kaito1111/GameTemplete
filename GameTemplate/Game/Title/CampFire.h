#pragma once
/// <summary>
/// キャンプファイヤーのクラス
/// タイトルで使われている
/// </summary>
class CampFire : public IGameObject
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
	/// モデルの位置を設定する
	/// </summary>
	/// <param name="pos">位置</param>
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	/// <summary>
	/// 最小光量を取得する
	/// </summary>
	/// <returns>最小光量</returns>
	float GetMinLightPow() {
		float minLightPow = 1000.0f;
		for (float lightPow : m_lightPowArray) {
			minLightPow = min(lightPow, minLightPow);
		}
		return minLightPow;
	}
	/// <summary>
	/// 光の強さを取得する
	/// </summary>
	/// <returns>光量</returns>
	const float GetLightPow()const {
		return m_LightPower;
	}
	/// <summary>
	/// 最大光量を取得する
	/// </summary>
	/// <returns>最大光量</returns>
	float GetMaxLightPow() {
		float maxLightPow = 1.0f;
		for (float lightPow : m_lightPowArray) {
			maxLightPow = max(lightPow, maxLightPow);
		}
		return maxLightPow;
	}
private:
	SkinModelRender* m_Model = nullptr;			//キャンプファイヤーのモデル
	CVector3 m_Position = CVector3::Zero();		//モデルの位置
	PointLight* m_PointLight = nullptr;			//光源
	static const int m_lightPowArraySize = 15;	//光の光量パターンの配列数
	const float m_lightPowArray[m_lightPowArraySize]
		= {
		270.0f,260.0f,220.0,300.0f,40.0f,
		300.0f,280.0f,250.0f,290.0f,240.0f,
		320.0f,260.0f,250.0f,260.0f,270.0f
	};											//光量パターンを決める配列
	int m_currentLigPowNum = 0;					//現在有効な光量
	float m_LightPower = 0.0f;					//光の強さ
	SoundSource m_Sound;						//キャンプファイヤーの音
	float m_ScaleTime = 0.0f;					//どの配列を有効にするかの変数
	Effect* m_effect = nullptr;					//炎のエフェクト
};

