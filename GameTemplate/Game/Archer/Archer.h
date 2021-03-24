#pragma once
#include "State/IArcherState.h"
#include "Player/Player.h"
class Archer : public IGameObject
{
	enum State {
		Idle,
		Attack,
		Damage,
		Deth,
		Num
	};
public:
	~Archer() {};

	bool Start()override;
	void Update()override;
	void OnDestroy()override;

	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	void TryAttackState() {
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	void SetIdleState() {
		m_NextState = State::Idle;
	}

	void SetSpownPosition(const CVector3& pos) {
		m_SpownPositon = pos;
	}

	void SetRotation(const CQuaternion& rot) {
		m_Rotation = rot;
	}

private:

	bool IsAttack();

	void UpdateState(int st);

	void UpdateSprite();

	void HpPosAdjustment();

	void OnEventListener(const wchar_t* clipName);
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Position = CVector3::Zero();
	CVector3 m_SpownPositon = CVector3::Zero();
	CQuaternion m_Rotation = CQuaternion::Identity();
	Animation m_Animation;
	AnimationClip m_AnimationClip[State::Num];
	IArcherState* m_ActiveState = nullptr;
	int m_State = State::Idle;
	int m_NextState = State::Idle;
	Player* m_Player = nullptr;
	CVector3 m_Forward = CVector3::Front();

	SpriteRender* m_HpTopSprite = nullptr;		//hpのスプライト
	CVector3 m_HpPosition = CVector3::Zero();	//hpのスプライト位置
	float m_Hp = 50.0f;							//hp
	const float m_SpriteSize = 0.025f;			//hpのサイズを調整

	SpriteRender* m_HpUnderSprite = nullptr;	//hpの下にあるスプライト
	const float m_height = 150.0f;				//敵の身長
	int m_AttackPattarn = 0;					//どの攻撃判定が発生している？

	CharacterController m_CharaCon;				//キャラコン
};