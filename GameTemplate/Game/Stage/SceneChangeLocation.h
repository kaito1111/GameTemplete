#pragma once
class Player;
class Fade;
/// <summary>
/// エリチェンを担当するクラス
/// </summary>
class SceneChangeLocation final : public IGameObject
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
	/// モデルの位置を設定
	/// </summary>
	/// <param name="pos">位置</param>
	void SetPosition(const CVector3& pos) {
		m_Pos = pos;
	}
	/// <summary>
	/// 現在のステージを読み込むファイルパス
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void SetFilePath(const wchar_t* filePath) {
		wcscpy(m_FilePath, filePath);
	}
private:
	CVector3 m_Pos = CVector3::Zero();	//エリチェンの範囲の中心
	Player* m_player = nullptr;			//プレイヤーポインタ
#ifdef _DEBUG
	SkinModelRender* m_Skin = nullptr;	//エリチェンの範囲を表したモデル
#endif
	wchar_t m_FilePath[256] = {};		//現在のステージのファイルパス
	Fade* m_Fade = nullptr;				//エリチェン時に流すフェード
};

