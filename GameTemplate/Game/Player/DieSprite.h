#pragma once
/// <summary>
/// 死んだ時に呼ぶクラス
/// </summary>
class DieSprite final : public IGameObject
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
	bool Start()override;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
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
	void OnDestroy()override;

private:
	SpriteRender* m_DieSprite = nullptr;				//ダイスプライト
	float m_DieAlpha = 0.0f;							//ダイスプライトの透明度

	SpriteRender* m_LogoSprite = nullptr;				//ロゴスプライト
	float m_LogoAlpha = 0.0f;							//ロゴスプライトの透明度

	SpriteRender* m_PlayerDieChoicesSprite = nullptr;	//選択肢のスプライト
	float m_ChoicesAlpha = 0.0f;						//選択肢のスプライトの透明度

	SpriteRender* m_ChoicesIConSprite = nullptr;		//矢印のスプライト
	CVector3 m_IConPos = { -100.0f,50.0f,0.0f };		//矢印の位置

	bool IsReset = false;								//選択肢を選んだかどうかのフラグ
};