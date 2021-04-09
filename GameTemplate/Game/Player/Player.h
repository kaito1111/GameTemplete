#pragma once
#include "character/CharacterController.h"

class IPlayerState;

class Player : public IGameObject
{
public:
	////状態の種類をenum化
	enum State {
		State_Idle,		//待機中
		State_Run,		//走り中
		State_Backstep,	//バックステップ中。
		State_Attack,	//攻撃中
		State_RollingAttack,//ローリングアタック中
		State_Damage,	//ダメージ中
		State_Num
	};
	//アニメーションの数
	//ステートと同じ場所ににしないとバグります
	enum AnimePattern {
		idle,			//待機
		walk,			//走り
		Back,			//バックステップ
		Attack,			//攻撃
		RollingAttack,	//ローリングアタック
		Damage,			//ダメージ
		AnimeNum
	};
	Player();
	~Player();
	//初期化
	bool Start()override;
	//更新
	void Update()override;
	//削除された瞬間に呼ばれる
	void OnDestroy()override;

	//位置を取得
	CVector3 GetPosition() {
		return m_Pos;
	}
	//攻撃位置を取得
	CVector3 AttackPos() {
		return m_AttackPos;
	}
	//hpを取得
	int GetHp() {
		return m_Hp;
	}
	/// <summary>
	/// 待機ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeIdleState() {
		if (!IsMove()) {
			m_NextState = State_Idle;
		}
	}
	/// /// <summary>
	/// 移動ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeMoveState()
	{
		if (IsMove()) {
			m_NextState = State_Run;
		}
	}
	/// <summary>
	/// バックステップステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeBackStepState()
	{
		if (IsBackStep()) {
			m_NextState = State_Backstep;
		}
	}
	/// <summary>
	/// 攻撃ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeAttackState()
	{
		if (IsAttack()) {
			m_NextState = State_Attack;
		}
	}
	/// <summary>
	/// 回転攻撃ステートに切り替えることが出来たら切り替える。
	/// </summary>
	void TryChangeRollingAttackState()
	{
		if (IsRollingAttack()) {
			m_NextState = State_RollingAttack;
		}
	}
	//待機状態へ遷移
	void SetIdleState() {
		m_NextState = State_Idle;
	}
	//アニメーションを再生
	void PlayAnimation()
	{
		//待機状態の処理
		m_Animation.Play(m_state, 0.2f);
	}
	/// <summary>
	/// アニメーションの再生速度に乗算される値を設定。
	/// </summary>
	/// <param name="mulSpeed"></param>
	void SetMulAnimSpeed(const float mulSpeed) 
	{
		m_mulAnimSpeed = mulSpeed;
	}
	/// <summary>
	/// プレイヤーのアニメーション再生中？
	/// </summary>
	/// <returns></returns>
	bool IsPlayAnimation() const {
		return m_Animation.IsPlaying();
	}
	//ダメージを受けた
	void HitDamage(const float damege) {
		//hpを減らす
		m_Hp -= damege;
		//ダメージ状態へ遷移
		m_NextState = State_Damage;
		//無敵時間を設定
		m_mutekiflame = 60;
	}
	//無敵時間を取得
	int GetMutekiFlame() const {
		return m_mutekiflame;
	}

	//初期位置を設定
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}
	//回転率を設定
	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}
	//Hpを設定
	//エリアチェンジで使う
	void SetSpwonHp(const int hp) {
		m_Hp = hp;
	}

	//プレイヤーの高さを取得
	float GetHeight() const {
		return m_height;
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

	//スプライトを更新
	void UpdateSprite();

	/// <summary>
	/// 状態を切り替える。
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(int state);
private:
	bool m_ComboAttack = false;
	

	IPlayerState* m_currentState = nullptr;		//現在のステート。
	int m_state = State_Idle;					//プレイヤーの現在の状態。
	int m_NextState = State::State_Idle;		//次の状態。
	SkinModelRender* m_Model = nullptr;			//スキンモデル。
	CVector3 m_Pos = CVector3::Zero();			//位置
	CQuaternion m_Rot = CQuaternion::Identity();//回転量
	CVector3 m_MoveSpeed = CVector3::Zero();	//移動量
	CharacterController m_CharaCon;				//キャラコン
	
	float m_mulAnimSpeed = 1.0f;				//アニメーション速度に乗算する
	CVector3 m_AttackPos = CVector3::Zero();	//攻撃場所
	Animation m_Animation;						//アニメーション
	AnimationClip m_AnimeClip[AnimePattern::AnimeNum];//アニメーションクリップ

	SpriteRender* m_HpTopSprite = nullptr;		//上の絵
	CVector3 m_HpPosition = CVector3::Zero();	//絵の位置
	float m_Hp = 62.5;							//体力
	const float m_MaxHp = 62.5;					//最大体力
	const float m_SpriteSize = 0.025f;			//hpの絵を調整する定数

	SpriteRender* m_HpUnderSprite = nullptr;	//下の絵

	const float m_radius = 35.0f;				//キャラコンの横幅
	const float m_height =  110.0f;				//キャラコンの縦幅
	bool m_isInvokeAttackColli = false;			//攻撃判定が発生している？

	CVector3 m_forward = CVector3::Front();		//前方向

	int m_mutekiflame = 0;						//無敵時間

	SkinModelRender* m_HitModel = nullptr;		//デバッグ用のモデル

	CVector3 m_SpownPosition = CVector3::Zero();//初期位置
};

