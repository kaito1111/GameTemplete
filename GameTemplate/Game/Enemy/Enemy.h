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
	void HitDamege(const float damege);
private:
	//初期化場所
	bool Start()override;

	//モデルを初期化
	void SkinModelInit();

	//キャラコンを初期化
	//1行で終わるから無駄だけどわかりやすくするため　
	void CharaConInit();

	//HPスプライトを初期化
	void HpSpriteInit();
	//HPを敵のちょっと上に置き
	//Hpの位置を基点に合わせて修正
	void HpPosAdjustment();
	//TopSpriteを初期化
	void HpTopSpriteInit(const float sizeY,const CVector3& scale);
	//UnderSpriteを初期化
	void HpUnderSprite(const float sizeY, const CVector3& scale);

	//アニメーションを初期化
	void AnimetionInit();
	//更新
	void Update()override;

	//アニメーションイベント
	//EnemyAttackを作っている
	void OnAnimEvent(const wchar_t* eventName);
	//スプライトを更新
	void UpdateSprite();
	
	//歩くかの判定
	bool IsWalk()const;
	//攻撃するかを判定
	bool IsAttack()const;

	void Rotate()override;

	//ステートを切り替えるときに使用する
	//enumのstateを利用すると切り替えやすい。ていうか推奨
	void ChangeState(int st);

private:

	SpriteRender* m_HpTopSprite = nullptr;		//hpのスプライト
	CVector3 m_HpPosition = CVector3::Zero();	//hpのスプライト位置
	float m_Hp = 62.5f;							//hp
	//const float m_SpriteSize = 0.025f;			//hpのサイズを調整

	SpriteRender* m_HpUnderSprite = nullptr;	//hpの下にあるスプライト
	const float m_height = 150.0f;				//敵の身長
	int m_AttackPattarn = 0;					//どの攻撃判定が発生している？

	Animation m_Animation;						//アニメーション
	AnimationClip m_AniClip[Num];				//アニメーションの種類

	int m_State = State::Idle;					//現在のステートを記憶する
												//ステートを切り替えるときに使用する
	IEnemyState* m_ActiveState = nullptr;		//現在のステート
	int m_NextState = State::Idle;				//次のステート

	CVector3 m_AttackPos = CVector3::Zero();	//攻撃の場所

	EnemyAttack* attack = nullptr;				//攻撃判定
	Player* m_Player = nullptr;

};
