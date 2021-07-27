#pragma once
#include "character/characterController.h"
class Character :public IGameObject
{
public:
	enum HpScale {
		PlayerHP,
		EnemyHP,
		BossHP,
		Num
	};
	~Character() ;

	void Destroy();

	//初期位置を設定
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}

	//モデルの初期化
	void CharacterInit(wchar_t* filePath, float radius, float hight, const CVector3& pos);

	//回転処理を各自設定
	virtual void Rotate() = 0;

	//回転量を設定
	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}

	//位置を取得
	const CVector3& GetPosition() {
		return m_ModelPos;
	}

	//ここで動く
	void Move(CVector3& move);

	//モデルを更新する
	void CharacterModelUpdate();

	//前方向の更新をする
	virtual void ForwardUpdate();

	//移動量を取得
	CVector3 GetMoveSpeed()const {
		return m_MoveSpeed;
	}

	CQuaternion GetRot() {
		return m_ModelRot;
	}
	
	//hpと最大Hpを設定している
	void InitHpSprite(const float maxHp,const float hp, HpScale hpScale);

	//スプライトのhpの残りとかを計算している
	void SpriteUpdate();

	//攻撃が当たった時に呼ばれる
	//関数内にステートを変更する処理が入るので純粋仮想関数にする
	virtual	void HitDamage(const float damege) = 0;

	void Heal();

private:
	void SpriteInit(SpriteRender*& SpriteP,wchar_t* fileName);
	void HpPosAdjustment();
protected:
	SkinModelRender* m_Model = nullptr;			//モデル
	CVector3 m_ModelPos = CVector3::Zero();			//モデルの位置
	CQuaternion m_ModelRot = CQuaternion::Identity();//モデルの回転
	CVector3 m_ModelScale = CVector3::One();	//モデルの大きさ
	CharacterController m_CharaCon;				//キャラコン

	CVector3 m_MoveSpeed = CVector3::Zero();	//移動量
	CVector3 m_forward = CVector3::Front();		//前方向
	CVector3 m_SpownPosition = CVector3::Zero();//初期位置

	SpriteRender* m_HpUnderSprite = nullptr;
	SpriteRender* m_HpTopSprite = nullptr;
	CVector3 m_HpPosition = CVector3::Zero();
	float m_Hp = 0.0f;
	float m_MaxHp = 0.0f;
	float m_Hight = 0.0f;
	HpScale m_HpScale;
	float m_HpScaleList[HpScale::Num] = { 100.0f,100.0f,120.f };
	//スプライトの基点をずらしているので
	//そのズレを修正
	float m_spriteFix = -50.0f;

	CVector3 m_Left = CVector3::Left();
	SpriteRender* m_HpTopTranslucentSprite = nullptr;  //Hpの半透明スプライト
	float m_TranslucentScale = 1.0f;
	float m_HoldTimer = 3.0f;
};

