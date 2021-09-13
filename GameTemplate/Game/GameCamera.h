#pragma once
class Player;
#include "character/CharacterController.h"
#include "graphics/SpringCamera.h"

/// <summary>
/// プレイヤーを追いかけるカメラクラス
/// </summary>
class GameCamera :public IGameObject
{
public:
	/// <summary>
	/// カメラの初期化時の回転量
	/// </summary>
	/// <param name="rot">初期回転量</param>
	const void SetStartAngle(const CQuaternion& rot) {
		m_StartRot = rot;
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
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override final;
	
	CVector3 m_Pos = CVector3::Zero();					//カメラの位置
	CVector3 m_Target = CVector3::Zero();				//カメラの注視点
	Player* m_player = nullptr;							//プレイヤーのポインタ
	float m_AngleX = 0.0f;								//カメラのX軸回転
	float m_AngleY = 0.0f;								//カメラのY軸回転
	CharacterController m_CharaCon;						//キャラコン
	CQuaternion m_StartRot = CQuaternion::Identity();	//カメラの初期回転量
	CVector3 PlayerCameraLeave = { 0.0f,100.0f,500.0f };//カメラとの距離
	SpringCamera m_springCamera;						//スプリングカメラ
	float m_refleshTimer = 1.0f;						//カメラを再更新する時間
};