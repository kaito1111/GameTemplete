#pragma once
class Player;
/// <summary>
/// アーチャーが攻撃するときに呼ばれるクラス
/// </summary>
class ArcherAttack final : public IGameObject
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
	/// 位置を設定
	/// </summary>
	/// <param name="pos">位置</param>
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
private:
#ifdef _DEBUG
	SkinModelRender* m_Model = nullptr;
#endif
	CVector3 m_Position = CVector3::Zero();	//モデルの位置
	Player* m_Player = nullptr;				//プレイヤーポインタ
	SoundSource m_DamageSound;				//攻撃音
};

