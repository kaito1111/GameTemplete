#pragma once
#include "character/CharacterController.h"

class IPlayerState;

class Player : public IGameObject
{
public:
	//プレイヤーのステート
	enum State {
		State_Idle,		//待機中
		State_Run,		//走り中
		State_Backstep,	//バックステップ中。
		State_Attack,
		State_RollingAttack,
		State_Num
	};
	enum AnimePattern {
		idle,
		walk,
		Cloase,
		Back,
		Attack,
		RollingAttack,
		AnimeNum
	};
	Player();
	~Player();
	bool Start();
	void Update();

	CVector3 GetPosition() {
		return m_Pos;
	}

	CVector3 AttackPos() {
		return m_AttackPos;
	}
	/// <summary>
	/// 状態を切り替える。
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(State state);

	void TryChangIdleState() {
		if (!IsMove()) {
			ChangeState(State_Idle);
		}
	}
	/// <summary>
	/// 移動ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeMoveState()
	{
		if (IsMove()) {
			ChangeState(State_Run);
		}
	}
	/// <summary>
	/// バックステップステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeBackStepState()
	{
		if (IsBackStep()) {
			ChangeState(State_Backstep);
		}
	}
	/// <summary>
	/// 攻撃ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeAttackState()
	{
		if (IsAttack()) {
			ChangeState(State_Attack);
		}
	}
	/// <summary>
	/// 回転攻撃ステートに切り替えることが出来たら切り替える。
	/// </summary>
	void TryChangeRollingAttackState()
	{
		if (IsRollingAttack()) {
			ChangeState(State_RollingAttack);
		}
	}
	void PlayAnimation(AnimePattern anim)
	{
		//待機状態の処理
		m_Animation.Play(anim, 0.2f);
	}
	/// <summary>
	/// アニメーションの再生速度に乗算される値を設定。
	/// </summary>
	/// <param name="mulSpeed"></param>
	void SetMulAnimSpeed(float mulSpeed) 
	{
		m_mulAnimSpeed = mulSpeed;
	}
	/// <summary>
	/// プレイヤーのアニメーション再生中？
	/// </summary>
	/// <returns></returns>
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	void HitDamage(float damege) {
		m_Hp -= damege;
	}
private:
	/// <summary>
	/// 状態の更新。
	/// </summary>
	void UpdateState();
	/// <summary>
	/// 移動するか判定
	/// </summary>
	/// <returns>trueが帰ってきたら移動する。</returns>
	bool IsMove() const;
	/// <summary>
	/// バックステップを行う？
	/// </summary>
	/// <returns></returns>
	bool IsBackStep() const;
	/// <summary>
	/// 通常攻撃する？
	/// </summary>
	/// <returns></returns>
	bool IsAttack();
	/// <summary>
	/// 回転攻撃する？
	/// </summary>
	/// <returns></returns>
	bool IsRollingAttack();
	/// <summary>
	/// プレイヤーの移動処理
	/// </summary>
	void PlayerMove();
	/// <summary>
	/// プレイヤーの旋回処理。
	/// </summary>
	void PlayerRotate();
	/// <summary>
	/// アニメーションイベントが発生した時に呼ばれる処理。
	/// </summary>
	/// <param name="eventName"></param>
	void OnAnimEvent(const wchar_t* eventName);

	void UpdateSprite();
private:
	bool m_ComboAttack = false;
	

	IPlayerState* m_currentState = nullptr;		//現在のステート。
	State m_state = State_Idle;					//プレイヤーの現在の状態。
	SkinModelRender* m_Model = nullptr;			//スキンモデル。
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	CVector3 m_MoveSpeed = CVector3::Zero();
	CharacterController m_CharaCon;
	
	float m_mulAnimSpeed = 1.0f;	//アニメーション速度に乗算する
	CVector3 m_AttackPos = CVector3::Zero();
	Animation m_Animation;
	AnimationClip m_AnimeClip[AnimePattern::AnimeNum];

	SpriteRender* m_HpTopSprite = nullptr;
	CVector3 m_HpPosition = CVector3::Zero();
	float m_Hp = 62.5;
	float m_SpriteSize = 0.025f;

	SpriteRender* m_HpUnderSprite = nullptr;

	float m_radius = 30.0f;
	float m_height =  110.0f;
	bool m_isInvokeAttackColli = false;	//攻撃判定が発生している？
};

