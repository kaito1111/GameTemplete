#pragma once
#include "physics/PhysicsStaticObject.h"
class Wall final : public IGameObject
{
public:
	Wall() {};
	~Wall() {};

	bool Start();
	void Update();
	void SetPosition(CVector3 Pos) {
		m_Pos = Pos;
	}
	void SetRotation(CQuaternion Rot) {
		m_Rot = Rot;
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	PhysicsStaticObject m_Pysics;
};

