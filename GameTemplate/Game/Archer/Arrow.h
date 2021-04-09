#pragma once
class Archer;
class ArcherAttack;
class Arrow : public IGameObject
{
public:
	//デストラクタ
	~Arrow()
	{
	}
	//初期化
	void Init(Archer* arc);
	//更新
	void Update()override;
	//消えるときに呼ばれる
	void OnDestroy()override;
	//弓にバインドするときにセットする
	void SetArrowBindFlag() {
		m_isBaindArrow = true;
	}
	void SetShot() {
		IsShot = true;
	}
private:
	SkinModelRender* m_Model = nullptr;	//モデル
	Archer* m_Archer = nullptr;			//矢を出すクラス
	bool m_isBaindArrow = false;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	bool IsShot = false;
	float m_ElapsedTime = 0.0f;
	ArcherAttack* m_ArcherAttack = nullptr;
};