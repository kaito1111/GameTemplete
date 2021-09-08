#pragma once
class Fade;
/// <summary>
/// ボスを倒したときにスプライトや
/// ゲームループ部分を管理しているクラス
/// </summary>
class HuntedSprite final :public IGameObject
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
	SpriteRender* m_HuntSprite = nullptr;	//ハントスプライト
	SpriteRender* m_BrackSprite = nullptr;	//ハントスプライトが出ているときに
											//周りをちょっとだけ暗くするエフェクト的なスプライト
	float m_HuntAlpha = 0.0f;				//ハントスプライトの透明度

	bool m_ReSet = false;					//選択肢を選んだかどうかのフラグ
	SoundSource m_HuntSound;				//クリア時の音楽
};