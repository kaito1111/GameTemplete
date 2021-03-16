#pragma once
class Fade :public IGameObject
{
public:
	bool Start();
	void Update();
	void OnDestroy()override;

	void SetFailName(wchar_t* fName) {
		wcsncpy(m_FilePath, fName,wcsnlen(fName,128));
	}
	float GetAlpha()const {
		return m_Alpha;
	}
private:
	SpriteRender* m_FadeSprite = nullptr;
	wchar_t m_FilePath[128] = {};
	float m_Alpha = 1.0f;
	float m_StayCount = 0;
	SpriteRender* m_LodingSprite = nullptr;
	float m_Angle = 0.0f;
	CVector3 m_LodingSpritePos = {800.0f,-200.0f,0.0f};
};

