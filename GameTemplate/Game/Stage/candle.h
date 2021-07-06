#pragma once
class Candle: public IGameObject
{
public:
	Candle() {};
	~Candle() {};

	bool Start()override final;
	void Update()override final;

	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_Rotation = rot;
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Position = CVector3::Zero();
	CQuaternion m_Rotation = CQuaternion::Identity();
	PointLight* m_PointLightRed = nullptr;//ŠO‘¤‚ÌŒõ‚ğÄŒ»‚·‚é
	float m_LightPower = 200.0f;
	float a = -8.0f; 
	CVector3 LightPos = CVector3::Zero();

	PointLight* m_PointLightYellow = nullptr;//“à‘¤‚ÌŒõ‚ğÄŒ»‚·‚é
};