#pragma once
class BossHpSprite :public IGameObject
{
public:
	BossHpSprite() {};
	~BossHpSprite() {};

	bool Start()override;
	void Update()override;
	void OnDestroy()override;
	void SetHp(float hp) {
		m_Hp = hp;
	}
private:
	SpriteRender* m_TopHpSprite = nullptr;
	SpriteRender* m_UnderHpSprite = nullptr;
	CVector3 m_Pos = { 0.0f,-390.0f ,0.0f};
	float m_Hp = 0.0f;
	float m_MaxHp = 0.0f;
	float m_AppearanceHpScale = 0.0f;
};

