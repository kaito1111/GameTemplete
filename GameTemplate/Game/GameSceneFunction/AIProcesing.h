#pragma once
#include "Character.h"
#include "Player/Player.h"
class AIProcesing:public Character
{
public:
	AIProcesing() {
		m_player = FindGO<Player>("player");
	}
	~AIProcesing() {};
	void AIWalk();
	void AIAttack(float damage, float eria,char* AttackName);	
protected:
	Player* m_player = nullptr;
};