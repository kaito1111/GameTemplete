#pragma once
class Fade;
class Stage;
class Player;
class GameCamera;
class CampFire;
/// <summary>
/// タイトル作らす
/// </summary>
class Title final : public IGameObject
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

private:
	SpriteRender* m_TitleSprite = nullptr;	//PleaseAnyButtonと書かれたスプライト
	Fade* m_fade = nullptr;					//シーン切り替え時に使うフェード
	Stage* m_Stage = nullptr;				//ステージのポインタ
	Player* m_Player = nullptr;				//プレイヤーのポインタ
	GameCamera* m_camera = nullptr;			//カメラのポインタ
	CampFire* m_camp = nullptr;				//キャンプファイヤーのポインタ
	float m_Alpha = 0.5f;					//スプライトの透明度
};

