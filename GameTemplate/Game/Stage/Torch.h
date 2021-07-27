#pragma once
class Torch : public IGameObject
{
public:
	Torch() {}
	~Torch(){}

	bool Start()override final;
	void Update()override final;
	void OnDestroy()override final;

	void SetPosition(const CVector3& pos)
	{
		m_Position = pos;
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Position = CVector3::Zero();
	PointLight* m_PoinsLight = nullptr;
	float m_LightPower = 500.0f;
	float a = -1.5f;
	Effect* m_Effect = nullptr;
};

