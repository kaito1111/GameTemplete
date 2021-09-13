#pragma once

#include "Player/Player.h"
class Stage;
class GameCamera;
#include "Enemy/EnemySpawner.h"
#include "Archer/ArcherSpowner.h"
#include "Boss/BossSpawn.h"
//#include "Manual.h"
/// <summary>
/// ゲームクラス
/// </summary>
class Game final : public IGameObject
{
public:

	/// <summary>
	/// ステージクラスに渡すファイルパス
	/// L"Assets/level/"はいらない
	/// </summary>
	/// <param name="filePath"></param>
	void SetLevelFilePath(wchar_t* filePath) {
		wchar_t fileName[256] = L"Assets/level/";
		wcscat(fileName, filePath);
		wcscpy(m_LevelFilePath, fileName);
	}

	/// <summary>
	/// プレイヤーのHpを取得する
	/// ステージの切り替え時に使用する
	/// </summary>
	/// <returns></returns>
	const int GetPlayerHp() const {
		return m_Player->GetHp();
	}
	/// <summary>
	/// Hpを引き継ぐ
	/// ステージの切り替え時に使用する
	/// </summary>
	/// <param name="hp">プレイヤーのHp</param>
	void SetPlayerHp(const int hp) {
		m_SpownHp = hp;
	}
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
	Player* m_Player = nullptr;					//プレイヤーのポインタ
	Stage* m_Stage = nullptr;					//ステージのポインタ
	GameCamera* m_Camera = nullptr;				//カメラのポインタ
	wchar_t m_LevelFilePath[256] = {};			//ステージで使うファイルパスを保存する文字列
	int m_SpownHp = 62.5f;						//プレイヤーのHp
	EnemySpawner* m_EnemySpawner = nullptr;		//スケルトンの親クラス
	ArcherSpowner* m_ArcherSpawner = nullptr;	//アーチャーの親クラス
	BossSpawn* m_BossSpawner = nullptr;			//ボスの親クラス
	SoundSource m_BGM;							//ゲームのBGM
	DirectionLight* m_Direction = nullptr;		//太陽に見せかけるライト
};