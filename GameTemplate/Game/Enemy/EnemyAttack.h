#pragma once
class Player;
class EnemyAttack : public IGameObject
{
public:
	EnemyAttack();
	~EnemyAttack();
	void Init(float Damege, float Aria,const CVector3& AttackPos) {
		m_Area = Aria;
		m_Damege = Damege;
		m_Position = AttackPos;
	}
	bool Start();
	void Update();
	void OnDestroy()override;
private:
	float m_Damege = 0.0f;
	float m_Area = 0.0f;
	Player* m_Player = nullptr;
	CVector3 m_Position = CVector3::Zero();
	SkinModelRender* m_AttackModel = nullptr;
};

