#pragma once
class Player;
class Attack : public IGameObject
{
public:
	Attack() {};
	~Attack() {};
	//èâä˙âª
	void Init(float Damege, float Aria, const CVector3& pos) {
		m_Area = Aria;
		m_Damege = Damege;
		m_Position = pos;
		m_Player = FindGO<Player>("player");
		m_AttackModel = NewGO<SkinModelRender>(0);
		m_AttackModel->Init(L"DebugShere.cmo");
		m_AttackModel->SetPosition(m_Position);
		CVector3 ModelScale = { m_Area,m_Area,1.0f };
		m_AttackModel->SetScale(ModelScale);
	}
	//çXêV
	void Update();
	void OnDestroy()override;
private:
	float m_Damege = 0.0f;
	float m_Area = 0.0f;
	Player* m_Player = nullptr;
	CVector3 m_Position = CVector3::Zero();
	SkinModelRender* m_AttackModel = nullptr;
};

