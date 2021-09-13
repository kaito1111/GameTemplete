#pragma once
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"
class PhysicsStageObject;
class Player;
class SceneChangeLocation;
class ReturnLocatoin;
class Candle;
class Torch;
/// <summary>
/// ステージのクラス
/// </summary>
class Stage final :public IGameObject
{
public:
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
	/// ステージを読み込む関数
	/// この関数でしかステージを作れない
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void Load(const wchar_t* filePath);
	/// <summary>
	/// ステージで読み込んだプレイヤーの初期位置を返す　
	/// </summary>
	/// <returns>プレイヤーの初期位置</returns>
	const CVector3 GetPlayerPos()const {
		return m_SpownPlayerPosition;
	}
	/// <summary>
	/// ステージで読み込んだプレイヤーの回転量を返す
	/// </summary>
	/// <returns>プレイヤーの回転量</returns>
	const CQuaternion GetPlayerRotation() const{
		return m_PlayerSpawnRot;
	}
	/// <summary>
	/// タイトルシーン中にプレイヤーのいる位置
	/// </summary>
	/// <returns>プレイヤーの位置</returns>
	const CVector3 GetTitlePos() const{
		return m_TitlePos;
	}
	/// <summary>
	/// タイトルシーンのカメラの位置
	/// </summary>
	/// <returns></returns>
	const CVector3 GetTitleCameraPos() const{
		return m_TitleCameraPos;
	}
	/// <summary>
	/// タイトルシーンのカメラの注視点
	/// </summary>
	const CVector3 GetTitleCameraTarget()const {
		return m_TitleCameraTarget;
	}
private:
	std::vector< PhysicsStageObject*> m_PSOList;			//静的物理オブジェクト達のポインタリスト				
	Level m_level;											//ステージを読み込むレベル
	wchar_t m_LevelFilePath[256] = {};						//レベルで読み込むときに使うファイルパス
	CVector3 m_SpownPlayerPosition = CVector3::Zero();		//プレイヤーの初期位置
	CQuaternion m_PlayerSpawnRot = CQuaternion::Identity();	//プレイヤーの初期回転量
	Sky* m_sky = nullptr;									//空のキューブマップ
	CVector3 m_TitlePos = CVector3::Zero();					//プレイヤーがタイトルにいるときの位置
	CVector3 m_TitleCameraPos = CVector3::Zero();			//タイトルシーンのカメラの位置
	CVector3 m_TitleCameraTarget = CVector3::Zero();		//タイトルシーンのカメラの注視点
	std::vector<SceneChangeLocation*> m_SCLoc;				//次のシーンの移動するクラスのリスト
	std::vector<ReturnLocatoin*> m_RCLoc;					//前のシーンに戻るクラスのリスト
	std::vector<Candle*> m_Can;								//キャンドルのリスト
	std::vector<Torch*> m_Torch;							//松明のリスト
};

