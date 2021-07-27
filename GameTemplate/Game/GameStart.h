#pragma once
class Fade;
class Game;
class GameStart :	public IGameObject
{
public:
	GameStart(){}
	~GameStart(){}

	bool Start()override final;
	void Update()override final;

private: 
	Fade* m_fade = nullptr;
	Game* m_Game = nullptr;
};

