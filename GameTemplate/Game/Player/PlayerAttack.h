#pragma once
class PlayerAttack : public IGameObject
{
public:
	PlayerAttack();
	~PlayerAttack();

	void Init(float atack, float aria,const CVector3& pos,float attackFrame) {
		m_Attack = atack;
		m_Aria = aria;
		m_Position = pos;
		m_AttackFrame = attackFrame;
	}

	bool Start();
	void Update();
private:
	CVector3 m_Position = CVector3::Zero();
	float m_Attack = 0.0f;
	float m_Aria = 0.0f;
	float m_AttackFrame = 0.0f;
	float m_DeltaTime = 0.0f;
};