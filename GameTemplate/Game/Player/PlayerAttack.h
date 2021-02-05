#pragma once
class Enemy;
class PlayerAttack : public IGameObject
{
public:
	PlayerAttack();
	~PlayerAttack();

	void Init(float damege, float aria,const CVector3& pos,float attackFrame) {
		m_damege = damege;
		m_Aria = aria;
		m_Position = pos;
		m_AttackFrame = attackFrame;
	}

	bool Start();
	void Update();
private:
	CVector3 m_Position = CVector3::Zero();
	Enemy* m_enemy = nullptr;
	float m_damege = 0.0f;
	float m_Aria = 0.0f;
	float m_AttackFrame = 0.0f;
	float m_DeltaTime = 0.0f;
};