#pragma once

/// <summary>
/// ボスのHPのスプライトクラス
/// </summary>
class BossHpSprite final :public IGameObject
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
	bool Start()override;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
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
	/// HPをセット。
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHp(float hp) 
	{
		m_Hp = hp;
	}
private:
	SpriteRender* m_TopHpSprite = nullptr;			// 画面上部のHPバー。
	SpriteRender* m_UnderHpSprite = nullptr;		
	CVector3 m_Pos = { -653.0f,-490.0f ,0.0f};
	float m_Hp = 0.0f;
	float m_MaxHp = 0.0f;
	float m_AppearanceHpScale = 0.0f;
	CVector3 m_HpScale = CVector3::One();
	SpriteRender* m_HpTopTranslucentSprite = nullptr;
	bool m_HpInit = false;
	float m_TranslucentScale = 0.0f;		//半透明スプライトのスケール
	float m_HoldTime = 1.0f;				//Hpスケールをキープするスケール
	CVector3 m_TranslunceSpriteScale = CVector3::One();
};

