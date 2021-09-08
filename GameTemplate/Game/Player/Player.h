#pragma once
#include "character/CharacterController.h"
#include "GameSceneFunction/Anime.h"
class IPlayerState;
class HuntedSprite;
class IWeapon;
class PlayerAttack;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final : public Anime
{
public:
	//プレイヤーのスタミナ消費量を表した列挙型
	enum  StaminaCostList {
		StaminaRun = 1,				//走り中
		StaminaRolling = 30,		//ローリング中
		StaminaAttack = 20,			//攻撃中
		StaminaRollingAttack = 60,	//ローリング攻撃中
		StaminaNum					
	};
	//状態の種類を表した列挙型
	enum State {
		Title,			//タイトルの待機中（座っている）
		Stand,			//立つ
		Idle,			//待機中
		Walk,			//走り中
		Roling,			//ローリング中。
		Attack,			//攻撃中
		RollingAttack,	//ローリングアタック中
		Damage,			//ダメージ中
		Die,			//死亡
		GameClear,		//ゲームクリア
		Num
	};
	/// <summary>
	/// インスタンスが生成されると、一度だけ呼ばれる開始処理
	/// </summary>
	/// <remarks>
	/// UnityのStart()関数の仕様に準拠。
	/// </remarks>
	/// <returns>
	/// trueが帰ってきたら、初期化完了。
	/// 複数フレームにわたって初期化をしたい場合は、
	/// 初期化完了までfalseを返す。
	/// </returns>
	bool Start()override final;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override final;
	/// <summary>
	/// インスタンスが破棄される時に呼ばれる関数。
	/// </summary>
	/// <remarks>
	/// 本エンジンで実装している、ゲームオブジェクトを削除する
	/// DeleteGO関数は、すぐにインスタンスを削除するわけではなく、
	/// 1フレーム遅れてインスタンスが削除される。
	/// そのため、デストラクタの呼び出しが、DeleteGOの呼び出しから1フレーム遅れることとなる。
	/// DeleteGOが呼ばれたタイミングで、行いたい終了処理はOnDestroy()に記述する。
	/// </remarks>
	void OnDestroy()override final;

	/// <summary>
	/// プレイヤーモデルの位置を取得
	/// </summary>
	/// <returns>モデルの位置</returns>
	CVector3 GetPosition() {
		return m_ModelPos;
	}
	/// <summary>
	/// プレイヤーの攻撃位置を取得
	/// </summary>
	/// <returns>攻撃位置</returns>
	CVector3 AttackPos() {
		return m_AttackPos;
	}
	/// <summary>
	/// プレイヤーの残りHpを取得
	/// </summary>
	/// <returns>Hpを取得</returns>
	float GetHp() const{
		return m_Hp;
	}
	/// <summary>
	/// 待機ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeIdleState() {
		if (!IsMove()) {
			m_NextState = State::Idle;
		}
	}
	/// /// <summary>
	/// 移動ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeMoveState()
	{
		if (IsMove()) {
			m_NextState = State::Walk;
		}
	}
	/// <summary>
	/// バックステップステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeBackStepState()
	{
		if (IsBackStep()) {
			m_NextState = State::Roling;
		}
	}
	/// <summary>
	/// 攻撃ステートに切り替えることができたら切り替える。
	/// </summary>
	void TryChangeAttackState()
	{
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}
	/// <summary>
	/// 回転攻撃ステートに切り替えることが出来たら切り替える。
	/// </summary>
	void TryChangeRollingAttackState()
	{
		if (IsRollingAttack()) {
			m_NextState = State::RollingAttack;
		}
	}
	/// <summary>
	/// タイトル状態へ遷移
	/// </summary>
	void SetTitleState() {
		m_NextState = State::Title;
	}
	/// <summary>
	/// 立つ状態へ遷移
	/// </summary>
	void SetStandingState() {
		m_NextState = State::Stand;
	}
	/// <summary>
	/// 待機状態へ遷移
	/// </summary>
	void SetIdleState() {
		m_NextState = State::Idle;
	}
	/// <summary>
	/// ゲームクリアステートへ遷移
	/// </summary>
	void SetClearState() {
		m_NextState = State::GameClear;
	}
	/// <summary>
	/// アニメーションを再生
	/// </summary>
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
	/// <summary>
	/// ダメージを受けた
	/// </summary>
	/// <param name="damege">ダメージ量</param>
	void HitDamage(const float damege) override{

		//hpを減らす
		m_Hp -= damege;
		//ダメージ状態へ遷移
		m_NextState = State::Damage;
		//Hpが0以下になったら死ぬ
		if (m_Hp <= 0.0f) {
			m_NextState = State::Die;
			m_Hp = 0;
		}
	}

	/// <summary>
	/// 初期位置を設定
	/// </summary>
	/// <param name="pos"></param>
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}
	/// <summary>
	/// 回転率を設定
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}
	/// <summary>
	/// Hpを設定
	/// エリアチェンジで使う
	/// </summary>
	/// <param name="hp"></param>
	void SetSpwonHp(const float hp) {
		m_Hp = hp;
	}

	/// <summary>
	/// プレイヤーの身長を取得
	/// </summary>
	/// <returns>キャラコンの高さ</returns>
	float GetHeight() const {
		return m_height;
	}

	/// <summary>
	/// プレイヤーの状態を取得
	/// </summary>
	/// <returns></returns>
	int GetState()const {
		return m_state;
	}
	/// <summary>
	/// プレイヤーのスタミナ残量を取得
	/// </summary>
	/// <returns>スタミナの残量</returns>
	float GetStamina()const {
		return m_Stamina;
	}
	/// <summary>
	/// スタミナを設定する
	/// </summary>
	/// <param name="st"></param>
	void SetStamina(const float st) {
		m_Stamina = st;
	}
	/// <summary>
	/// スタミナをつくことができるか
	/// </summary>
	void IsStaminaRest() {
		m_StaminaRest = false;
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
	void Rotate();
	/// <summary>
	/// アニメーションイベントが発生した時に呼ばれる処理。
	/// </summary>
	/// <param name="eventName"></param>
	void OnAnimEvent(const wchar_t* eventName);

	/// <summary>
	/// 状態を切り替える。
	/// </summary>
	/// <param name="state"></param>
	void ChangeState(int state);

	/// <summary>
	/// アニメーションを初期化する
	/// </summary>
	void AnimetionInit();

private:
	bool m_ComboAttack = false;	

	IPlayerState* m_currentState = nullptr;		//現在のステート。
	int m_state = State::Idle;					//プレイヤーの現在の状態。
	int m_NextState = State::Idle;				//次の状態。
	CVector3 m_MoveSpeed = CVector3::Zero();	//移動量
	
	float m_mulAnimSpeed = 1.0f;				//アニメーション速度に乗算する
	CVector3 m_AttackPos = CVector3::Zero();	//攻撃場所
	AnimationClip m_AnimeClip[State::Num];		//アニメーションクリップ

	const float m_SpriteSize = 0.025f;			//hpの絵を調整する定数

	const float m_height =  110.0f;				//キャラコンの縦幅
	bool m_isInvokeAttackColli = false;			//攻撃判定が発生している？

#ifdef _DEBUG
	SkinModelRender* m_HitModel = nullptr;		//デバッグ用のモデル
#endif
	CVector3 m_SpownPosition = CVector3::Zero();//初期位置
	HuntedSprite* m_HuntedSprite = nullptr;		//ゲームクリア時に出るスプライト
	SoundSource m_WalkSound;					//歩く音
	SoundSource m_WalkSound2;					//歩く音が被った時に流れる予備音声
	SoundSource m_SwingSound;					//武器を振った音

	IWeapon* m_weapon = nullptr;				//武器のスキン
	PlayerAttack* m_PlAttack = nullptr;			//プレイヤーの攻撃判定
	PointLight* m_myLuminous = nullptr;			//自分を光らせるポイントライト　名前は適当
	SpriteRender* m_StaminaSprite = nullptr;	//スタミナ残量のスプライト
	float m_Stamina = 100.0f;					//スタミナ値
	SpriteRender* m_StaminaFrame = nullptr;		//スタミナのフレーム
	bool m_StaminaRest = true;					//スタミナが回復できるか
	float m_RestStopTime = 1.0f;				//スタミナを使い切ると回復出来なくなるクールタイム
	bool m_IsLastAttack = false;				//この攻撃が最後？
	float m_NewClearTime = 0.0f;				//ClearスプライトをNewするタイミング

	SoundSource m_RollingSound;					//回転時に流れる音
};

