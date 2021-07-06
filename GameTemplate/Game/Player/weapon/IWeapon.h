#pragma once
class IWeapon
{
public:
	IWeapon() {};
	~IWeapon() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	
	void SetPosition(CVector3 pos) {
		m_Position = pos;
	}
	void SetRotation(CQuaternion rot) {
		m_Rotation = rot;
	}
protected:
	CVector3 m_Position = CVector3::Zero();
	CQuaternion m_Rotation = CQuaternion::Identity();
};

