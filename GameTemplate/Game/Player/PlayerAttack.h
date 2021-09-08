#pragma once
#include "GameSceneFunction/Anime.h"

/// <summary>
/// プレイチャーが攻撃するときに呼ばれるクラス
/// </summary>
class PlayerAttack final : public IGameObject
{
public:
	/// <summary>
	/// 攻撃のパラメータを決める関数
	/// </summary>
	/// <param name="atack">攻撃力</param>
	/// <param name="aria">攻撃範囲</param>
	/// <param name="pos">攻撃場所</param>
	void Init(float atack, float aria,const CVector3& pos) {
		m_Attack = atack;
		m_Aria = aria;
		m_AttackPos = pos;
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
	bool Start();
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update();
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
	/// 当たったかどうか
	/// １度当たっていたら攻撃判定がなくなる
	/// </summary>
	/// <returns>trueで当たった</returns>
	bool IsHit() {
		return m_Hit;
	}
private:
	CVector3 m_AttackPos = CVector3::Zero();	//攻撃場所
	float m_Attack = 0.0f;						//攻撃力
	float m_Aria = 0.0f;						//攻撃範囲
	bool m_Hit = false;							//攻撃が１回ヒットした
#ifdef _DEBUG
	SkinModelRender* m_AttackModel = nullptr;	//攻撃範囲を表したモデル
#endif
	SoundSource m_DamageSound;					//攻撃がヒットした音
};