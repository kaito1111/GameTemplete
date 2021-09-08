#pragma once
#include "Anime.h"
#include "Player/Player.h"
class Attack;
/// <summary>
/// 敵キャラやボスが使う処理をまとめたもの
/// 継承を使って利用する
/// </summary>
class AIProcesing:public Anime
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	AIProcesing() {
		m_player = FindGO<Player>("player");
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AIProcesing() ;

	/// <summary>
	/// プレイヤーを追いかける処理
	/// </summary>
	void AIWalk();

	/// <summary>
	/// プレイヤーを攻撃する処理
	/// </summary>
	void AIAttack(float damage, float eria,char* AttackName=nullptr);	

	/// <summary>
	/// プレイヤーの位置を取得
	/// </summary>
	/// <returns>プレイヤーの位置を返す</returns>
	CVector3 GetPlayerPos() {
		return m_player->GetPosition();
	}

	/// <summary>
	/// プレイヤーが遠いとHpを見えなくする
	/// </summary>
	void UpdateHpAlpha();

	/// <summary>
	/// enemyが死んでから攻撃が死んでは遅いので
	/// 動的に消せるようにした
	/// </summary>
	void DeleteAttack();
protected:
	Player* m_player = nullptr;		//プレイヤーのポインタ
	float AttackReach = 50.0f;		//攻撃の肩から腕までの距離
	Attack* m_HaveAttack = nullptr;	//この攻撃クラスを利用して攻撃する
	float m_HpAlhpa = 0.0;			//距離によって視認できるかを見る
	float m_deltaTime = 0.0f;		//Hpが見えなくなる時間
};