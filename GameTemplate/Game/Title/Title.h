#pragma once
class Fade;
class Stage;
class Player;
class GameCamera;
class CampFire;
class Title final : public IGameObject
{
public :
	bool Start()override final;
	void Update()override final;
	void OnDestroy()override final;

private:
	SpriteRender* m_TitleSprite = nullptr;
	Fade* m_fade = nullptr;
	Stage* m_Stage = nullptr;
	Player* m_Player = nullptr;
	GameCamera* m_camera = nullptr;
	CampFire* m_camp = nullptr;
	float m_Alpha = 0.5f;
	float m_AlphaAdd = 0.009f;
};

