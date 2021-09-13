#pragma once
class Boss;
/// <summary>
/// フェードクラス
/// シーン切り替え時に呼ばれるクラス
/// </summary>
class Fade final :public IGameObject
{
private:
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
public:
	/// <summary>
	///	フェードの透明度を取得
	/// </summary>
	/// <returns></returns>
	const float GetAlpha()const {
		return m_Alpha;
	}
private:
	SpriteRender* m_FadeSprite = nullptr;				//フェードを担当するスプライト
	float m_Alpha = 0.0f;								//スプライトの透明度
	float m_StayCount = 0;								//真っ暗にする時間（初期化などをこのタイミングでする）
	SpriteRender* m_LodingSprite = nullptr;				//右下でぐるぐる回ってるスプライト
	float m_Angle = 0.0f;								//右下のスプライトの回転量
	CVector3 m_LodingSpritePos = {800.0f,-200.0f,0.0f};	//右下のスプライトの位置
};

