#pragma once
#include "character/CharacterController.h"
#include "EnemyAttack.h"
class IEnemyState;
#include "Player/Player.h"
#include "GameSceneFunction/AIProcesing.h"
//敵
class Enemy :public AIProcesing
{
public:
	//状態の種類をenum化
enum State {
	Attack,
	Idle,
	Walk,
	Damege,
	Down,
	Num
};
	Enemy();
	~Enemy();
	//敵が消えた瞬間に呼ばれる
	void OnDestroy()override;
public:
	//アニメーションを再生
	//enumのStateを使うと便利。推奨
	void PlayAnimation(State st) {
		m_Animation.Play(st, 0.2f);
	}
	//アニメーションを再生中？
	bool IsPlayingAnimation() const{
		return m_Animation.IsPlaying();
	}


	//プレイヤーを攻撃するか判定
	void TryChangeAttackState() {
		//trueで攻撃
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	//プレイヤーを追いかけるか調べる
	void TryChangeWalk() {
		//trueで歩く
		if (IsWalk()) {
			m_NextState = State::Walk;
		}
	}

	//IdelStateに遷移したいとき専用
	void SetIdleState() {
		m_NextState = State::Idle;
	}

	//プレイヤーからの攻撃が当たったら呼ばれる
	void HitDamage(const float damege)override;

	//プレイヤー方向に歩く
	void EnemyWalk() {
		AIWalk();
	}
private:
	//初期化場所
	bool Start()override;

	//アニメーションを初期化
	void AnimetionInit();
	//更新
	void Update()override;

	//アニメーションイベント
	//EnemyAttackを作っている
	void OnAnimEvent(const wchar_t* eventName);
	
	//歩くかの判定
	bool IsWalk()const;
	//攻撃するかを判定
	bool IsAttack()const;

	//回転処理
	void Rotate()override;

	//ステートを切り替えるときに使用する
	//enumのstateを利用すると切り替えやすい。ていうか推奨
	void ChangeState(int st);

private:
	float m_Hp = 62.5f;							//hp

	int m_AttackPattarn = 0;					//どの攻撃判定が発生している？

	AnimationClip m_AniClip[Num];				//アニメーションの種類

	int m_State = State::Idle;					//現在のステートを記憶する
												//ステートを切り替えるときに使用する
	IEnemyState* m_ActiveState = nullptr;		//現在のステート
	int m_NextState = State::Idle;				//次のステート

	CVector3 m_AttackPos = CVector3::Zero();	//攻撃の場所

	Player* m_Player = nullptr;

};
