#pragma once
class Player;
#include "character/CharacterController.h"
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	void SetStartAngle(CQuaternion rot) {
		m_StartRot = rot;
	}
private:
	bool Start();
	void Update();
	
	CVector3 m_Pos = CVector3::Zero();
	CVector3 m_Target = CVector3::Zero();
	Player* m_player = nullptr; 
	float m_AngleX = 0.0f;
	float m_AngleY = 0.0f; 
	CharacterController m_CharaCon;
	CQuaternion m_StartRot = CQuaternion::Identity();
};