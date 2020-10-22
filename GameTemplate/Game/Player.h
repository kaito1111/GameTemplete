#pragma once
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
private:
	SkinModelRender* m_model = nullptr;									//スキンモデル。
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	float m_angle;
	CharacterController m_CharaCon;
};

