#pragma once
class IBossState;
class Player;
#include "GameSceneFunction/AIProcesing.h"
#include "character/CharacterController.h"
class Boss : public AIProcesing
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
		m_ModelPos = pos;
	}

	CVector3 GetPosition() const {
		return m_ModelPos;
	}

	CVector3 GetPlayerPos()const {
		return m_player->GetPosition();
	}

	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
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

	void Move(CVector3& move);
private:	
	Animation m_Animation;
	AnimationClip m_AnimationClip[StateNum];

	IBossState* m_ActiveState = nullptr;

	State m_CurrentState = State::AppearanceRoar;
	State m_NextState = State::Walk;

	const float m_CoolTimeRoar = 500;
	float m_RoarTime = 0;

	CVector3 m_AttackPos = CVector3::Zero();

	SkinModelRender* m_HitModel = nullptr;		//デバッグ用のモデル
private:
 
	void ChengeState(const State& state);
	void Rotate()override;

};

