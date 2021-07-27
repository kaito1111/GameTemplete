#pragma once
class DieSprite final : public IGameObject
{
public:
	~DieSprite() {};

	bool Start()override;
	void Update()override;
	void OnDestroy()override;

private:
	SpriteRender* m_DieSprite = nullptr;
	float m_DieAlpha = 0.0f;

	SpriteRender* m_LogoSprite = nullptr;
	float m_LogoAlpha = 0.0f;

	SpriteRender* m_PlayerDieChoicesSprite = nullptr;
	float m_ChoicesAlpha = 0.0f;

	SpriteRender* m_ChoicesIConSprite = nullptr;
	CVector3 m_IConPos = { 0.0f,50.0f,0.0f };

	bool IsReset = false;
	int m_Rezult = 0;
};

