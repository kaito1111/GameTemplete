#pragma once
#include "character/CharacterController.h"
#include "EnemyAttack.h"
class Player;
class Enemy : public IGameObject
{
enum AnimePattern{
	Attack,
	Idle,
	Walk,
	Damage,
	Num
};
enum State {
	Attack,
	Idle,
	Walk,
	Damege,
	Num
};
public:
	Enemy();
	~Enemy();

	void SetPlayer(Player* pl) {
		m_Player = pl;
	}

	void Damege(float damege) {
		m_Hp -= damege;
	}
	const CVector3& GetPosition() {
		return m_Pos;
	}
	void PlayAnimation(AnimePattern pat) {

	}
private:
	bool Start()override;
	void Update()override;

	void EnemyRot();
	void OnAnimEvent(const wchar_t* eventName);
	void UpdateSprite();

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
	float m_height = 100.0f;
	int m_AttackPattarn = 0;	//çUåÇîªíËÇ™î≠ê∂ÇµÇƒÇ¢ÇÈÅH
	EnemyAttack* m_EnemyAttack;

	Animation m_Animation;
	AnimationClip m_AniClip[AnimePattern::Num];

	State m_State = State::Idle;
};