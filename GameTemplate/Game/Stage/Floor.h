#pragma once
class Floor final : public IGameObject
{
public:
	Floor() {};
	~Floor() {};

	bool Start();
	void Update();
	
	void SetPosition(CVector3 pos) {
		m_Pos = pos;
	}

	void SetRotation(CQuaternion rot) {
		m_Rot = rot;
	}

private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	CVector3 m_Scale = CVector3::One();
};