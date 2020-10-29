#pragma once

class Player;
class Stage;
class GameCamera;

class Game : public IGameObject
{
public:
	Game();
	~Game();

private:
	bool Start()override;
	void Update()override;
	void OnDestroy()override;
private:
	Player* m_Player = nullptr;
	Stage* m_Stage = nullptr;
	GameCamera* m_Camera = nullptr;
};