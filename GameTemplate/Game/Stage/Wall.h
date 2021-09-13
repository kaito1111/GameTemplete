#pragma once
#include "physics/PhysicsStaticObject.h"
/// <summary>
/// 壁のクラス
/// </summary>
class Wall final : public IGameObject
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
	/// モデルの位置を設定する
	/// </summary>
	/// <param name="Pos">位置</param>
	const void SetPosition(const CVector3& Pos) {
		m_Pos = Pos;
	}
	/// <summary>
	/// モデルの回転量を設定する
	/// </summary>
	/// <param name="Rot">回転量</param>
	const void SetRotation(const CQuaternion& Rot) {
		m_Rot = Rot;
	}
private:
	SkinModelRender* m_Model = nullptr;				//壁のモデル
	CVector3 m_Pos = CVector3::Zero();				//モデルの位置
	CQuaternion m_Rot = CQuaternion::Identity();	//モデルの回転量
	PhysicsStaticObject m_Pysics;					//静的物理オブジェクト
};