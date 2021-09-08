#pragma once
#include "character/CharacterController.h"
class IEnemyState;
#include "Player/Player.h"
#include "GameSceneFunction/AIProcesing.h"
/// <summary>
/// スケルトン
/// </summary>
class Enemy final :public AIProcesing
{
public:
	/// <summary>
	/// 状態を表す列挙型
	/// </summary>
enum State {
	Attack,
	Idle,
	Walk,
	Damege,
	Down,
	Num
};
public:
	/// <summary>
	/// アニメーションを再生
	/// </summary>
	/// <param name="st">
	/// 現在の状態が入る
	/// enumのStateを使うと便利。推奨
	/// </param>
	void PlayAnimation(State st) {
		m_Animation.Play(st, 0.2f);
	}
	/// <summary>
	/// アニメーションを再生中？
	/// </summary>
	/// <returns>trueなら再生している</returns>
	bool IsPlayingAnimation() const{
		return m_Animation.IsPlaying();
	}

	/// <summary>
	/// プレイヤーを攻撃するか判定
	/// </summary>
	void TryChangeAttackState() {
		//trueで攻撃
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	/// <summary>
	/// プレイヤーを追いかけるか調べる
	/// </summary>
	void TryChangeWalk() {
		//trueで歩く
		if (IsWalk()) {
			if (!m_WalkSound.IsPlaying()) {
				m_WalkSound.Play();
			}
			m_NextState = State::Walk;
		}
	}

	/// <summary>
	/// IdelStateに遷移したいとき専用
	/// </summary>
	void SetIdleState() {
		m_NextState = State::Idle;
	}

	/// <summary>
	/// プレイヤーからの攻撃が当たったら呼ばれる
	/// </summary>
	/// <param name="damege">ダメージ量</param>
	void HitDamage(const float damege)override;

	/// <summary>
	/// プレイヤー方向に歩く
	/// </summary>
	void EnemyWalk() {
		AIWalk();
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
	bool Start()override;

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
	/// アニメーションを初期化
	/// </summary>
	void AnimetionInit();
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;

	/// <summary>
	/// eventNameからアニメーションイベントを使うタイミングをフックして処理を書く
	/// </summary>
	/// <param name="eventName">maxで登録したイベントの名前</param>
	void OnAnimEvent(const wchar_t* eventName);
	
	/// <summary>
	/// 歩行状態へ移行できるか？
	/// </summary>
	/// <returns>trueで、できる</returns>
	bool IsWalk()const;
	/// <summary>
	/// 攻撃状態へ移行できるか？
	/// </summary>
	/// <returns>trueで、できる</returns>
	bool IsAttack()const;

	/// <summary>
	/// モデルの回転処理
	/// </summary>
	void Rotate()override;

	/// <summary>
	/// 状態を変更する関数
	/// </summary>
	/// <param name="state">次の状態</param>
	void ChangeState(int st);

private:
	AnimationClip m_AniClip[Num];				//アニメーションの種類

	int m_State = State::Idle;					//現在のステートを記憶する
												//ステートを切り替えるときに使用する
	IEnemyState* m_ActiveState = nullptr;		//現在のステート
	int m_NextState = State::Idle;				//次のステート

	CVector3 m_AttackPos = CVector3::Zero();	//攻撃の場所

	Player* m_Player = nullptr;					//プレイヤーポインタ

	SoundSource m_WalkSound;					//歩くときになる音
	SoundSource m_SwingSound;					//剣を振るときになる音
	SoundSource m_AttackVoice;					//攻撃時に喋る
};
