#pragma once
class PlayerAttack : public IGameObject
{
public:
	PlayerAttack();
	~PlayerAttack();

	void Init(float atack, float aria,const CVector3& pos) {
		m_Attack = atack;
		m_Aria = aria;
		m_Position = pos;
	}

	bool Start();
	void Update();
	void OnDestroy()override;
private:
	CVector3 m_Position = CVector3::Zero();
	float m_Attack = 0.0f;
	float m_Aria = 0.0f;
	bool m_Hit = false;//�U�����P��q�b�g����
	SkinModelRender* m_AttackModel = nullptr;
};