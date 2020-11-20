#pragma once
#include "character/CharacterController.h"
class Player;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	void SetPlayer(Player* pl) {
		m_Player = pl;
	}

	void Hit();
private:
	bool Start()override;
	void Update()override;

	void EnemyRot();
private:
	SkinModelRender* m_Skin = nullptr;
	CVector3 m_Pos = { 200.0f,0.0f,200.0f };
	CQuaternion m_Rot = CQuaternion::Identity();
	CVector3 m_Scale = CVector3::One()*0.3f;
	CharacterController m_CharaCon;
	Player* m_Player = nullptr;

	SkinModelRender* m_DownModel = nullptr;
	float m_DownAngle = 0.0f;
};