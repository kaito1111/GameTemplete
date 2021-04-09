#pragma once
#include "State/IArcherState.h"
#include "Player/Player.h"
class Arrow;
class Archer : public IGameObject
{
	//状態の種類をenum化
	enum State {
		Idle,
		Attack,
		Damage,
		Deth,
		Num
	};
public:
	~Archer() {};
	//初期化
	bool Start()override;
	//更新
	void Update()override;
	//死んだときに呼ばれる関数
	void OnDestroy()override;

	//プレイヤーのいる方向に向く
	void PlayerFacing();

	//アニメーションを再生しているか
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	//攻撃の状態に遷移するか
	void TryAttackState() {
		//攻撃の状態に遷移できるか
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	//待機状態へ遷移する
	void SetIdleState() {
		m_NextState = State::Idle;
	}

	//初期位置を設定する
	void SetSpownPosition(const CVector3& pos) {
		m_SpownPositon = pos;
	}

	//回転量を設定する
	void SetRotation(const CQuaternion& rot) {
		m_Rotation = rot;
	}
	/// <summary>
	/// スケルトンに設定されているアタッチボーンから、矢の位置と回転を計算する
	/// </summary>
	void CalcArrowPosAndRotationFromAttachBone(CVector3& pos, CQuaternion& rot, const wchar_t* AttachName, const wchar_t* TargetName);
	/// <summary>
	/// 矢をくっつけるボーンを取得する。
	/// </summary>
	/// <returns></returns>
	Bone* GetArrowAttachBone() const
	{
		return m_Model->GetModel().FindBone(L"arrow_attach");

	}
	Bone* GetArrowAttachBone2() const
	{
		return m_Model->GetModel().FindBone(L"arrow_attach");
	}
	//弓の骨にアタッチするか
	bool IsAttachArrow()const {
		return m_isAttachArrow;
	}
	//弓をアーチャーのリストから削除
	void ArrowListPop() {
		m_ArrowList.pop_front();
	}

	bool IsFacingFlag()const{
		return m_IsPlayerFacing;
	}

	void SetFacingFlag() {
		m_IsPlayerFacing = true;
	}
private:
	//攻撃できる？
	bool IsAttack();

	//モデルを初期化
	void InitModel();
	
	//アニメーションを初期化
	void InitAnimetion();

	//絵を初期化
	void InitSprite();

	//上のhpを初期化
	void InitHpTop();

	//下のHpを初期化
	void InitHpUnder();

	//アニメーションの更新
	void AnimationUpdate();


	//状態の切り替え
	void UpdateState(int st);

	//絵の更新
	void UpdateSprite();
	
	//hpの位置を修正
	void HpPosAdjustment();

	//前方向を更新
	void ForwardUpdate();

	//モデルの更新
	void ModelUpdate();

	//アニメーションイベントを設定
	void OnAnimEvent(const wchar_t* eventName);
	
private:
	SkinModelRender* m_Model = nullptr;				//モデル
	CVector3 m_Position = CVector3::Zero();			//位置
	CVector3 m_SpownPositon = CVector3::Zero();		//初期位置
	CQuaternion m_Rotation = CQuaternion::Identity();//回転量
	Animation m_Animation;							//アニメーション
	AnimationClip m_AnimationClip[State::Num];		//アニメーションクリップ
	IArcherState* m_ActiveState = nullptr;			//現在の状態
	int m_State = State::Idle;						//現在の状態
	int m_NextState = State::Idle;					//次の状態
	Player* m_Player = nullptr;						//プレイヤーのポインタ
	CVector3 m_Forward = CVector3::Front();			//前方向

	SpriteRender* m_HpTopSprite = nullptr;		//hpのスプライト
	CVector3 m_HpPosition = CVector3::Zero();	//hpのスプライト位置
	float m_Hp = 50.0f;							//hp
	const float m_SpriteSize = 0.025f;			//hpのサイズを調整

	SpriteRender* m_HpUnderSprite = nullptr;	//hpの下にあるスプライト
	const float m_height = 150.0f;				//敵の身長
	int m_AttackPattarn = 0;					//どの攻撃判定が発生している？

	CharacterController m_CharaCon;				//キャラコン

	bool m_isAttachArrow = false;
	std::list<Arrow*> m_ArrowList;

	bool m_IsPlayerFacing = true;			//プレイヤーを追従するか
};