#pragma once
#include "physics/PhysicsStaticObject.h"
/// <summary>
/// ステージの静的物理オブジェクトを作る
/// </summary>
class PhysicsStageObject final : public IGameObject
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
	bool Start() override final;
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
	/// この関数でしか設定していない
	/// </summary>
	/// <param name="Pos">モデルの位置</param>
	void SetPosition(const CVector3& Pos) {
		m_Pos = Pos;
	}

	/// <summary>
	/// モデルの回転量を設定
	/// この関数でしか設定していない
	/// </summary>
	/// <param name="Rot"></param>
	void SetRotation(CQuaternion Rot) {
		m_Rot = Rot;
	}

	/// <summary>
	/// モデルのファイルパスを設定
	/// この関数でしか設定していない
	/// </summary>
	/// <param name="name">ファイルパス</param>
	void SetObjectName(const wchar_t* name) {
		wcscpy(m_ObjectName,name);
	}
private:
	SkinModelRender* m_Model = nullptr;				//静的物理オブジェクトのモデル
	CVector3 m_Pos = CVector3::Zero();				//モデルの位置
	CQuaternion m_Rot = CQuaternion::Identity();	//モデルの回転量
	PhysicsStaticObject m_Pysics;					//静的物理オブジェクト
	wchar_t m_ObjectName[256] = {};					//モデルのファイルパス
};

