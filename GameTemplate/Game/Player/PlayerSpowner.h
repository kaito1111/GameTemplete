#pragma once
#include "Player/Player.h"
#include "level/Level.h"
/// <summary>
/// プレイヤークラスの親クラス
/// </summary>
class PlayerSpowner final : public IGameObject
{
public:
	
	/// <summary>
	/// レベルでロードするファイルパスをGameクラスで設定
	/// </summary>
	/// <param name="fileName">ロードしたいファイルパス</param>
	void SetFilePath(wchar_t* fileName) {
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
	bool Start()override final;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void OnDestroy()override final;

private:
	Player* m_player = nullptr;		//プレイヤーポインタ
	Level m_level;					//レベル
	wchar_t m_filePath[256] = {};	//レベルでロードするファイルパス
};

