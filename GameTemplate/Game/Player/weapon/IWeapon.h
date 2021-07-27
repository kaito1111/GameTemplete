#pragma once
class IWeapon
{
public:
	IWeapon() {};
	~IWeapon() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Delete() = 0;
	
	void SetPosition(CVector3 pos) {
		m_Position = pos;
	}
	void SetRotation(CQuaternion rot) {
		m_Rotation = rot;
	}
	SkinModelRender* GetModel() {
		return m_model;
	}
protected:
	CVector3 m_Position = CVector3::Zero();
	CQuaternion m_Rotation = CQuaternion::Identity();
	SkinModelRender* m_model = nullptr;

};

