#pragma once
#include "Level/Level.h"

/// <summary>
/// ボスを出現させる親クラス
/// </summary>
class BossSpawn final : public IGameObject
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

	/// <summary>
	/// levelデータを読みこむ
	/// </summary>
	/// <param name="filePath">レベルファイルパスの名前</param>
	void SetFilePath(wchar_t* fileName) {
		wcscpy(m_FilePath, fileName);
	}

private:
	wchar_t m_FilePath[256];//レベルファイルパス
	Level m_Level;			//レベル　

};

