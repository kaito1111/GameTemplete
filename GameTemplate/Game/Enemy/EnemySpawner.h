#pragma once
#include "Enemy/Enemy.h"
#include "level/level.h"
/// <summary>
/// エネミーの親クラス
/// </summary>
class EnemySpawner final : public IGameObject
{
public:
	/// <summary>
	/// 敵の出てくるファイルパスをロード
	/// </summary>
	/// <param name="fileName">ファイルパス</param>
	void SetFilePath(const wchar_t* fileName) {
		wcscpy_s(m_filePath, fileName);
	}

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
private:
	Level m_Level;						//レベル
	std::vector<Enemy*> m_EnemyList;	//敵のリスト
	wchar_t m_filePath[256] = {};		//レベルをロードする用のファイルパス
};

