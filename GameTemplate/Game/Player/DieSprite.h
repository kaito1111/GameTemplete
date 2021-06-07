#pragma once
class DieSprite final : public IGameObject
{
public:
	~DieSprite() {};

	bool Start()override;
	void Update()override;
	void OnDestroy()override;

	int GetRezult() {
		if (g_pad[0].IsPress(enButtonA)) {
			if (m_ChoicesAlpha >= 1.0f) {
				return m_Rezult;
			}
		}
		return 1000;
	}
private:
	SpriteRender* m_DieSprite = nullptr;
	float m_DieAlpha = 0.0f;

	SpriteRender* m_LogoSprite = nullptr;
	float m_LogoAlpha = 0.0f;

	SpriteRender* m_PlayerDieChoicesSprite = nullptr;
	float m_ChoicesAlpha = 0.0f;

	SpriteRender* m_ChoicesIConSprite = nullptr;
	CVector3 m_IConPos = CVector3::Zero();

	int m_Rezult = 0;
};

