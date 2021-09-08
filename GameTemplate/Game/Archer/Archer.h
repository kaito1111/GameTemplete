#pragma once
#include "State/IArcherState.h"
#include "GameSceneFunction/AIProcesing.h"

/// <summary>
/// Archerクラスが使う矢クラス
/// </summary>
class Arrow;

/// <summary>
/// アーチャークラス
/// </summary>
class Archer final : public AIProcesing
{
	/// <summary>
	/// 状態を表す列挙型
	/// </summary>
	enum State {
		Idle,
		Attack,
		Damage,
		Deth,
		Num
	};
public:
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
	bool Start()override;
	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;
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
	void OnDestroy()override;

	/// <summary>
	/// プレイヤーのいる方向に向く
	/// </summary>
	void Rotate();

	/// <summary>
	/// アニメーションを再生しているか
	/// </summary>
	/// <returns>trueでアニメーションが流れている</returns>
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	/// <summary>
	/// 攻撃の状態に遷移するか
	/// </summary>
	void TryAttackState() {
		//攻撃の状態に遷移できるか
		if (IsAttack()) {
			m_NextState = State::Attack;
		}
	}

	/// <summary>
	/// 待機状態へ遷移する
	/// </summary>
	const void SetIdleState() {
		m_NextState = State::Idle;
	}

	/// <summary>
	/// 初期位置を設定する
	/// </summary>
	/// <param name="pos">初期位置</param>
	const void SetSpownPosition(const CVector3& pos) {
		m_SpownPositon = pos;
	}

	/// <summary>
	/// 回転量を設定する
	/// </summary>
	/// <param name="rot">回転量</param>
	const void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
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

	/// <summary>
	/// 矢を弓の骨にアタッチするか
	/// </summary>
	/// <returns>trueならアタッチする</returns>
	bool IsAttachArrow()const {
		return m_isAttachArrow;
	}

	/// <summary>
	/// 矢をアーチャーのリストから削除
	/// </summary>
	void ArrowListPop() {
		if (m_ArrowList.size() != 0) {
			m_ArrowList.pop_front();
		}
	}

	/// <summary>
	/// プレイヤーの方向に向いているかどうか
	/// </summary>
	/// <returns>trueでプレイヤーの方向に向く</returns>
	bool IsFacingFlag()const{
		return m_IsPlayerFacing;
	}

	/// <summary>
	/// プレイヤーの方向に向く
	/// </summary>
	void SetFacingFlag() {
		m_IsPlayerFacing = true;
	}

	/// <summary>
	/// 攻撃を食らうと呼ばれる
	/// </summary>
	/// <param name="damege">ダメージ量</param>
	void HitDamage(const float damege)override;
private:
	/// <summary>
	/// 攻撃できる？
	/// </summary>
	/// <returns>攻撃できるならtrueが返る</returns>
	bool IsAttack();

	/// <summary>
	/// モデルを初期化
	/// </summary>
	void InitModel();
	
	/// <summary>
	/// アニメーションを初期化
	/// </summary>
	void InitAnimetion();

	/// <summary>
	/// アニメーションの更新
	/// </summary>
	void AnimationUpdate();

	/// <summary>
	/// 状態を変更する関数
	/// </summary>
	/// <param name="state">次の状態</param>
	void UpdateState(int st);

	/// <summary>
	/// eventNameからアニメーションイベントを使うタイミングをフックして処理を書く
	/// </summary>
	/// <param name="eventName">maxで登録したイベントの名前</param>
	void OnAnimEvent(const wchar_t* eventName);
	
private:
	CVector3 m_SpownPositon = CVector3::Zero();		//初期位置

	AnimationClip m_AnimationClip[State::Num];		//アニメーションクリップ

	IArcherState* m_ActiveState = nullptr;			//現在の状態
	int m_State = State::Idle;						//現在の状態
	int m_NextState = State::Idle;					//次の状態

	int m_AttackPattarn = 0;						//どの攻撃判定が発生している？

	bool m_isAttachArrow = false;					//矢が手につくタイミングかどうか
	std::list<Arrow*> m_ArrowList;					//矢を打つたびにリストに積む
	Arrow* m_HasArrow = nullptr;					//矢を打つ途中かどうか

	bool m_IsPlayerFacing = true;					//プレイヤーを追従するか

	SoundSource m_Shot;								//矢を打った時の音
	SoundSource m_Draw;								//矢を引いているときの音
};