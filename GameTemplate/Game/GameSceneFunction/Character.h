#pragma once
#include "character/characterController.h"
class Character :public IGameObject
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Character() {};
	/// <summary>
	/// このクラスは継承元として使われるのでOndestroyが使えないので
	/// 任意のタイミングでこの関数を呼びこのクラスで動的確保したものを削除する
	/// エラーは吐きませんが2回以上呼ばないように気を付けましょう(無駄なので)
	/// </summary>
	void Destroy();

	/// <summary>
	/// モデルの初期化
	/// </summary>
	/// <param name="filePath">モデルのファイルパス</param>
	/// <param name="radius">CharacterControllerに登録したい半径</param>
	/// <param name="hight">CharacterControllerに登録したい高さ</param>
	/// <param name="pos">CharacterControllerに登録したい初期位置</param>
	void CharacterInit(wchar_t* filePath,const float radius,const float hight, const CVector3& pos);

	/// <summary>
	/// モデルの回転処理を各自設定
	/// </summary>
	virtual void Rotate() = 0;

	/// <summary>
	/// モデルの回転量を設定
	/// </summary>
	/// <param name="rot">回転量</param>
	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}

	/// <summary>
	/// モデルの位置を取得
	/// </summary>
	/// <returns>モデルの位置</returns>
	const CVector3& GetPosition() const {
		return m_ModelPos;
	}

	/// <summary>
	/// レベルで取得した位置にモデルを配置する関数
	/// 生成時にしか呼ばれないのでSpownerクラスでしか呼ばれない、、、はず、、
	/// </summary>
	/// <param name="pos">初期位置</param>
	void SetSporwnModelPosition(const CVector3& pos) {
		m_ModelPos = pos;
	}
	/// <summary>
	/// CharacterControllerを動かす
	/// </summary>
	/// <param name="move">移動量</param>
	void Move(CVector3& move);

	/// <summary>
	/// モデルを更新する
	/// </summary>
	void CharacterModelUpdate();

	/// <summary>
	/// 前方向を更新する
	/// </summary>
	virtual void ForwardUpdate();

	/// <summary>
	/// モデルの移動量を取得
	/// </summary>
	/// <returns>移動量</returns>
	const CVector3& GetMoveSpeed()const {
		return m_MoveSpeed;
	}

	/// <summary>
	/// モデルの回転率を取得
	/// </summary>
	/// <returns>回転率</returns>
	const CQuaternion& GetRot()const {
		return m_ModelRot;
	}
	
	/// <summary>
	/// hpと最大Hpを初期化している
	/// </summary>
	/// <param name="maxHp">Hpの最大</param>
	/// <param name="hp">HP</param>
	/// <param name="Is3dDraw">3D描画しますか？</param>
	/// <param name="HpX">スプライトの横幅</param>
	/// <param name="HpY">スプライトの立幅</param>
	void InitHpSprite(const float maxHp,const float hp, bool Is3dDraw = true,float HpX= 100.0f,float HpY= 10.0f);

	/// <summary>
	/// スプライトのhpの残りとかを計算している
	/// </summary>
	void SpriteUpdate();

	/// <summary>
	/// 攻撃が当たった時に呼ばれる
	/// 関数内にステートを変更する処理が入るので純粋仮想関数にする
	/// </summary>
	/// <param name="damege">ダメージ量</param>
	virtual	void HitDamage(const float damege) = 0;

	/// <summary>
	/// 攻撃を受けた時、プレイヤーの攻撃が当たれば、
	/// TranslucentSpriteの位置まで回復する
	/// プレイヤーしか使っていない
	/// </summary>
	void Heal();

	/// <summary>
	/// 引数に持ってきた位置にHpスプライトを一律に移動させる関数
	/// </summary>
	/// <param name="pos">Hpスプライトの位置</param>
	void SetHpPosition(CVector3 pos) {
		m_HpTopSprite->SetPosition(pos);
		m_HpTopTranslucentSprite->SetPosition(pos);
		m_HpUnderSprite->SetPosition(pos);
	}

	/// <summary>
	/// 残りHpを取得
	/// </summary>
	/// <returns>残りHP</returns>
	float GetHp()const {
		return m_Hp;
	}
private:
	/// <summary>
	/// Hpスプライトの初期化
	/// </summary>
	/// <param name="SpriteP">動的確保するスプライトのポインタ</param>
	/// <param name="fileName">Hpスプライトに使う画像</param>
	/// <param name="Is3dDraw">3D描画しますか？</param>
	/// <param name="HpX">スプライトの横幅</param>
	/// <param name="HpY">スプライトの立幅</param>
	void SpriteInit(SpriteRender*& SpriteP, wchar_t* fileName, bool Is3dDraw, float HpX, float HpY);

	/// <summary>
	/// Hpスプライトがズレているので修正する関数
	/// </summary>
	void HpPosAdjustment();
protected:
	SkinModelRender* m_Model = nullptr;					//モデル
	CVector3 m_ModelPos = CVector3::Zero();				//モデルの位置
	CQuaternion m_ModelRot = CQuaternion::Identity();	//モデルの回転
	CVector3 m_ModelScale = CVector3::One();			//モデルの大きさ
	CharacterController m_CharaCon;						//キャラコン

	CVector3 m_MoveSpeed = CVector3::Zero();			//移動量
	CVector3 m_forward = CVector3::Front();				//前方向

	SpriteRender* m_HpTopSprite = nullptr;				//残りHpを表すスプライト
	SpriteRender* m_HpUnderSprite = nullptr;			//残りHpスプライトの下にあるスプライト
	
	CVector3 m_HpPosition = CVector3::Zero();			//Hpスプライトの位置
	float m_Hp = 0.0f;									//残りHp
	float m_MaxHp = 0.0f;								//最大Hp
	float m_Hight = 0.0f;								//高さ
	
	float m_spriteFix = -50.0f;							//スプライトの基点をずらしているのでそのズレを修正
														
	SpriteRender* m_HpTopTranslucentSprite = nullptr;   //Hpが徐々に減少していくのを表現するスプライト
	float m_TranslucentScale = 1.0f;					//m_HpTopTranslucentSpriteの透明度
	float m_HoldTimer = 0.0f;							//減るまでに待機する時間
};

