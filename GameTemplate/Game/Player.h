#pragma once
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

	CVector3 GetPosition() {
		return m_Pos;
	}
	//CVector3 GetForward() {
	//	return m_Forward;
	//}
private:
	SkinModelRender* m_model = nullptr;									//スキンモデル。
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	float m_angle=0.0f;
	CharacterController m_CharaCon;
	//CVector3 m_Forward = CVector3::Front();
};

