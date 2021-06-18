#pragma once
class Player;
class Fade;
class SceneChangeLocation final : public IGameObject
{
public:
	SceneChangeLocation() {};
	~SceneChangeLocation() {};

	bool Start();
	void Update();

	void OnDestroy()override;

	void SetPosition(CVector3 pos) {
		m_Pos = pos;
	}
	void SetFilePath(wchar_t* filePath) {
		wcscpy(m_FilePath, filePath);
	}
private:
	CVector3 m_Pos = CVector3::Zero();
	Player* m_player = nullptr;
#ifdef _DEBUG
	SkinModelRender* m_Skin = nullptr;
#endif
	float m_Eria = 50.0f;
	wchar_t m_FilePath[256] = {};
	Fade* m_Fade = nullptr;
};

