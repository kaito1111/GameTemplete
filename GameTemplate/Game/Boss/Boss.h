#pragma once
class Player;
class IBossState;
#include "character/CharacterController.h"
class Boss : public IGameObject
{
	enum State {
		Walk,
		Attack,
		NormalRoar,
		AppearanceRoar,
		Die,
		StateNum,
	};
public:
	~Boss() {};

	bool Start()override;
	void Update()override;

	void SetPosition(const CVector3& pos) {
		m_Pos = pos;
	}

	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}

	void PlayAnimation() {
		m_Animation.Update(gameTime().GetFrameDeltaTime());
	}
	
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}
	void IsChengeAttackState();
	void IsChengeNormalRoar();
	void SetWalkState() {
		m_NextState = State::Walk;
	}
	void WalkMove() {
		m_CharaCon.Execute(gameTime().GetFrameDeltaTime(), m_Forward*m_moveSpeed);
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	
	Animation m_Animation;
	AnimationClip m_AnimationClip[StateNum];

	IBossState* m_ActiveState = nullptr;

	State m_CurrentState = State::AppearanceRoar;
	State m_NextState = State::Walk;
	
	Player* m_player = nullptr;
	
	CVector3 m_Forward = CVector3::Front();

	CharacterController m_CharaCon;

	const float m_moveSpeed = 10.0f;

	const float m_CoolTimeRoar = 500;
	float m_RoarTime = 0;
private:
	void ChengeState(State state);

};

