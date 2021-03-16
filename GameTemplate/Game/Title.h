#pragma once
class Title : public IGameObject
{
public :
	bool Start();
	void Update();

private:
	SpriteRender* m_TitleSprite = nullptr;
};

