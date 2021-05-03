#pragma once
#include "Anime.h"
#include "Player/Player.h"
class AIProcesing:public Anime
{
public:
	//コンストラクタ
	AIProcesing() {
		m_player = FindGO<Player>("player");
	}
	//デストラクタ
	~AIProcesing() {};
	//プレイヤーを追いかける処理
	void AIWalk();
	//プレイヤーを攻撃する処理
	void AIAttack(float damage, float eria,char* AttackName);	
	//プレイヤーの位置を取得
	CVector3 GetPlayerPos() {
		return m_player->GetPosition();
	}
protected:
	Player* m_player = nullptr;//プレイヤーのポインタ
	const float AttackReach = 0.0f;	//攻撃の肩から腕までの距離
};