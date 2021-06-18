#pragma once
class Player;
class ArcherAttack final : public IGameObject
{
public:
	~ArcherAttack();
	bool Start()override;
	void Update()override;

	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
private:
#ifdef _DEBUG
	SkinModelRender* m_Model = nullptr;
#endif
	CVector3 m_Position = CVector3::Zero();
	Player* m_Player = nullptr;
	SoundSource m_DrawSound;
};

