#pragma once
class IBossState;
class Player;
#include "GameSceneFunction/AIProcesing.h"
#include "character/CharacterController.h"
#include "BossHpSprite.h"

/// <summary>
/// ボスクラス。
/// </summary>
class Boss final : public AIProcesing
{
	/// <summary>
	/// 状態を表す列挙型
	/// </summary>
	enum State {
		Walk,
		Attack,
		NormalRoar,
		AppearanceRoar,
		Down,
		Parry,
		Die,
		StateNum,
	};
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
	/// /ステート先でアニメーションをプレイする。
	/// </summary>
	/// <param name="nulTime">デルタタイムにアニメーションスピードを掛ける</param>
	void PlayAnimation(float nulTime=1.0f) {
		m_Animation.Update(gameTime().GetFrameDeltaTime()*nulTime);
	}
	/// <summary>
	///アニメーションを再生しているか？
	///アニメーションが終わってるかどうかで使っている
	/// </summary>
	/// <returns>trueでアニメーションが再生中</returns>
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	
	/// <summary>
	/// 攻撃状態へ移行できるか？
	/// </summary>
	void IsChengeAttackState();

	
	/// <summary>
	/// 咆哮状態へ移行できるか？
	/// </summary>
	void IsChengeNormalRoar();

	/// <summary>
	/// 歩行状態へ移行
	/// </summary>
	void SetWalkState() {
		m_NextState = State::Walk;
	}

	/// <summary>
	/// ダメージを受けた
	/// </summary>
	/// <param name="damege">HPが減るダメージ量、つまり攻撃力</param>
	void HitDamage(const float damege)override {
		///hpを減らす
		m_Hp -= damege;
		///ダメージが３分の１まで減ったら１度だけダウン状態に入る
		if (m_MaxHp / 3 > m_Hp&&IsParyy) {
			///ダメージ状態へ遷移
			m_NextState = State::Down;
			IsParyy = false;
		}
		///Hpが0以下になったら死ぬ
		if (m_Hp <= 0.0f) {
			m_NextState = State::Die;
			m_Hp = 0;
		}
	}
private:	
	AnimationClip m_AnimationClip[StateNum];	//アニメーションクリップ

	IBossState* m_ActiveState = nullptr;		//状態の処理が入っている　　

	State m_CurrentState = State::StateNum;		//現在の状態
	State m_NextState = State::AppearanceRoar;	//次の状態

	const float m_CoolTimeRoar = 12.0f;			//咆哮をしてから咆哮をするまでの時間
	float m_RoarTime = 0;						//咆哮してからの経過時間

#ifdef _DEBUG
	SkinModelRender* m_HitModel = nullptr;		//デバッグ用のモデル
#endif

	BossHpSprite* m_BossSprite = nullptr;		//ボスのHpを担当するクラス

	SoundSource m_RoarSound;					//咆哮中に流す音
	bool IsParyy = true;						//パリィができるかどうか（未実装）
private:
	/// <summary>
	/// 状態を変更する関数
	/// </summary>
	/// <param name="state">次の状態</param>
	void ChengeState(const State& state);

	/// <summary>
	/// モデルの回転処理
	/// </summary>
	void Rotate()override;

	/// <summary>
	/// アニメーションの初期化関数
	/// </summary>
	void AnimationInit();

	/// <summary>
	/// eventNameからアニメーションイベントを使うタイミングをフックして処理を書く
	/// </summary>
	/// <param name="eventName">maxで登録したイベントの名前</param>
	void OnAnimEvent(const wchar_t* eventName);

	/// <summary>
	/// BossHpSpriteを呼び出す関数
	/// </summary>
	void InitSprite();

};

