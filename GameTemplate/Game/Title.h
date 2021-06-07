#pragma once
class Fade;
class Title final : public IGameObject
{
public :
	bool Start();
	void Update();

private:
	SpriteRender* m_TitleSprite = nullptr;
	Fade* m_fade = nullptr;
};

