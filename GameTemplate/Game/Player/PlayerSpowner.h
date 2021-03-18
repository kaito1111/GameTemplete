#pragma once
#include "Player/Player.h"
class PlayerSpowner :public IGameObject
{
public:
	~PlayerSpowner() {};
	 
private:
	Player* m_player = nullptr;
	//wchat_t file
};

