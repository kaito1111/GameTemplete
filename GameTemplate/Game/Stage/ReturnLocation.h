#pragma once
class Player;
class ReturnLocatoin final : public IGameObject
{
public:
	ReturnLocatoin() {};
	~ReturnLocatoin() {};

	bool Start()override final;
	void Update()override final;
	void OnDestroy()override final;

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
	const float m_Eria = 75.0f;
	wchar_t m_FilePath[256] = {};
};