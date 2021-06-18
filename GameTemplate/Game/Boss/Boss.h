#pragma once
class IBossState;
class Player;
#include "GameSceneFunction/AIProcesing.h"
#include "character/CharacterController.h"
#include "BossHpSprite.h"
class Boss final : public AIProcesing
{
	//状態
	enum State {
		Walk,
		Attack,
		NormalRoar,
		AppearanceRoar,
		Down,
		Parry,
		Die,
		StateNum,
	};
public:
	~Boss() {};//デスストラクタ

	bool Start()override;//初期化関数を呼ぶ場所
	void Update()override;//更新関数を呼ぶ場所
	void OnDestroy()override;
	//ステート先でアニメーションをプレイする。
	void PlayAnimation() {
		m_Animation.Update(gameTime().GetFrameDeltaTime());
	}
	
	//アニメーションを再生しているか？
	//アニメーションが終わってるかどうかで使っている
	bool IsPlayAnimation() {
		return m_Animation.IsPlaying();
	}

	//攻撃状態へ移行できるか？
	void IsChengeAttackState();

	//咆哮状態へ移行できるか？
	void IsChengeNormalRoar();

	//歩行状態へ移行
	void SetWalkState() {
		m_NextState = State::Walk;
	}

	//ダメージを受けた
	void HitDamage(const float damege)override {
		//hpを減らす
		m_Hp -= damege;
		//ダメージが３分の１まで減ったら１度だけダウン状態に入る
		if (m_MaxHp / 3 > m_Hp&&IsParyy) {
			//ダメージ状態へ遷移
			m_NextState = State::Down;
			IsParyy = false;
		}
		//Hpが0以下になったら死ぬ
		if (m_Hp <= 0.0f) {
			m_NextState = State::Die;
			m_Hp = 0;
		}
	}
private:	
	AnimationClip m_AnimationClip[StateNum];//アニメーションクリップ

	IBossState* m_ActiveState = nullptr;	//状態の処理が入っている　　

	State m_CurrentState = State::AppearanceRoar;	//現在の状態
	State m_NextState = State::Walk;		//次の状態

	const float m_CoolTimeRoar = 10;	//咆哮をしてから咆哮をするまでの時間
	float m_RoarTime = 0;				//咆哮してからの経過時間

#ifdef _DEBUG
	SkinModelRender* m_HitModel = nullptr;		//デバッグ用のモデル
#endif

	BossHpSprite* m_BossSprite = nullptr;

	SoundSource m_RoarSound;
private:
	//ステートを変更する関数
	void ChengeState(const State& state);
	//モデルの回転処理
	void Rotate()override;
	//アニメーションを初期化関数
	void AnimationInit();

	void OnAnimEvent(const wchar_t* eventName);

	//咆哮処理を更新する関数
	void RoarUpdate();

	void InitSprite();

	bool IsParyy = true;	//パリィができるかどうか
};

