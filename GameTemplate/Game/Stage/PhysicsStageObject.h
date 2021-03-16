#pragma once
#include "physics/PhysicsStaticObject.h"
class PhysicsStageObject : public IGameObject
{
public:
	PhysicsStageObject() {};
	~PhysicsStageObject() {};

	bool Start();
	void OnDestroy()override;

	void SetPosition(CVector3 Pos) {
		m_Pos = Pos;
	}

	void SetRotation(CQuaternion Rot) {
		m_Rot = Rot;
	}

	void SetObjectName(const wchar_t* name) {
		wcscpy(m_ObjectName,name);
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	PhysicsStaticObject m_Pysics;
	wchar_t m_ObjectName[256] = {};
};

