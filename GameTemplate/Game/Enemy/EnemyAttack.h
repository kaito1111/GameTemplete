#pragma once
class Player;
class EnemyAttack : public IGameObject
{
public:
	EnemyAttack();
	~EnemyAttack();
	void Init(float Damege, float Aria,const CVector3& pos,float attackFrame) {
		m_Area = Aria;
		m_Damege = Damege;
		m_Position = pos;
		m_AttackFrame = attackFrame;
	}
	bool Start();
	void Update();
private:
	float m_Damege = 0.0f;
	float m_Area = 0.0f;
	Player* m_Player = nullptr;
	CVector3 m_Position = CVector3::Zero();
	float m_AttackFrame = 0.0f;
	float m_deltaFrame = 0.0f;
};

