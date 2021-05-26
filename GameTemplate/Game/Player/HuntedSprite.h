#pragma once
class Fade;
class HuntedSprite :public IGameObject
{
public:
	HuntedSprite() {};
	~HuntedSprite() {}

	bool Start()override;
	void Update()override;
	void OnDestroy()override;

private:
	SpriteRender* m_HuntSprite = nullptr;
	float m_HuntAlpha = 0.0f;

	SpriteRender* m_LogoSprite = nullptr;
	float m_LogoAlpha = 0.0f;

	float m_ChoicesAlpha = 0.0f;

	SpriteRender* m_ChoicesIConSprite = nullptr;
	CVector3 m_IConPos = CVector3::Zero();

	int m_Rezult = 0;
	Fade* m_fade = nullptr;
};