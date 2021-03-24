#pragma once
class Player;
class ArcherAttack : public IGameObject
{
public:
	~ArcherAttack();
	bool Start()override;
	void Update()override;

	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Position = CVector3::Zero();
	Player* m_Player = nullptr;
};

