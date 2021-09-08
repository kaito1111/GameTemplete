#pragma once
class Player;
/// <summary>
/// 攻撃の処理をまとめたクラス
/// </summary>
class Attack : public IGameObject
{
public:
	/// <summary>
	/// 攻撃の詳細を設定する初期化関数
	/// </summary>
	/// <param name="Damege"></param>
	/// <param name="Aria"></param>
	/// <param name="pos"></param>
	void Init(float Damege, float Aria, const CVector3& pos) {
		m_Area = Aria;
		m_Damege = Damege;
		m_Position = pos;
		m_Player = FindGO<Player>("player");
		m_DamageSound.Init(L"HitAttack.wav");
#ifdef _DEBUG
		m_AttackModel = NewGO<SkinModelRender>(0);
		m_AttackModel->Init(L"DebugShere.cmo");
		m_AttackModel->SetPosition(m_Position);
		CVector3 ModelScale = { m_Area,m_Area,1.0f };
		m_AttackModel->SetScale(ModelScale);
#endif
	}
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update() override;
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
	float m_Damege = 0.0f;						//攻撃力
	float m_Area = 0.0f;						//攻撃範囲
	Player* m_Player = nullptr;					//プレイヤーのポインタ
	CVector3 m_Position = CVector3::Zero();		//攻撃位置
#ifdef _DEBUG
	SkinModelRender* m_AttackModel = nullptr;	//攻撃範囲を表したモデル
#endif
	SoundSource m_DamageSound;					//攻撃音
};

