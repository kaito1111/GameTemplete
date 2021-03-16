#pragma once
#include "character/CharacterController.h"
#include "EnemyAttack.h"
class IEnemyState;
#include "Player/Player.h"
class Enemy : public IGameObject
{
public:
enum State {
	Attack,
	Idle,
	Walk,
	Damege,
	Down,
	Num
};
	Enemy();
	~Enemy();
	void OnDestroy()override;
public:
	void SetPlayer(Player* pl) {
		m_Player = pl;
	}

	CVector3 GetPlayerPos() {
		return m_Player->GetPosition();
	}

	void HitDamege(float damege);

	const CVector3& GetPosition() {
		return m_Pos;
	}
	void PlayAnimation(State st) {
		m_Animation.Play(st, 0.2f);
	}
	bool IsPlayingAnimation() const{
		return m_Animation.IsPlaying();
	}


	void TryChangeAttackState() {
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	void TryChangeWalk() {
		if (IsWalk()) {
			m_NextState = State::Walk;
		}
	}

	bool IsDamage()const;

	void SetIdleState() {
		m_NextState = State::Idle;
	}

	void Move(CVector3 move);

	void SetSpownPos(CVector3 pos) {
		m_SpownPosition = pos;
	}
	void SetRotation(CQuaternion rot) {
		m_Rot = rot;
	}
private:
	bool Start()override;
	void Update()override;

	void EnemyRot();
	void OnAnimEvent(const wchar_t* eventName);
	void UpdateSprite();
	
	bool IsWalk()const;
	bool IsAttack()const;

	void CreateEnemyAttack();

	void ChangeState(int st);
private:
	SkinModelRender* m_Skin = nullptr;
	CVector3 m_Pos = { 200.0f,00.0f,200.0f };
	CQuaternion m_Rot = CQuaternion::Identity();
	CVector3 m_Scale = CVector3::One()*10.0f;
	CharacterController m_CharaCon;
	Player* m_Player = nullptr;

	CVector3 m_MoveSpeed = CVector3::Zero();

	SpriteRender* m_HpTopSprite = nullptr;
	CVector3 m_HpPosition = CVector3::Zero();
	float m_Hp = 62.5f;
	float m_SpriteSize = 0.025f;

	SpriteRender* m_HpUnderSprite = nullptr;
	float m_height = 150.0f;
	int m_AttackPattarn = 0;	//çUåÇîªíËÇ™î≠ê∂ÇµÇƒÇ¢ÇÈÅH

	Animation m_Animation;
	AnimationClip m_AniClip[Num];

	int m_State = State::Idle;

	IEnemyState* m_ActiveState = nullptr;
	int m_NextState = State::Idle;

	CVector3 m_forward = CVector3::Front();
	CVector3 m_AttackPos = CVector3::Zero();

	EnemyAttack* attack = nullptr;

	CVector3 m_SpownPosition = CVector3::Zero();
};
