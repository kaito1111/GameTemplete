#pragma once
#include "physics/PhysicsStaticObject.h"
class Stage :public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();

private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject m_phy;
};

