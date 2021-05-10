#pragma once
class Fade;
class Title : public IGameObject
{
public :
	bool Start();
	void Update();

private:
	SpriteRender* m_TitleSprite = nullptr;
	Fade* m_fade = nullptr;
};

