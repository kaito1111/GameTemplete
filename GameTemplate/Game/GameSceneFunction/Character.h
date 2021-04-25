#pragma once
#include "character/characterController.h"
class Character :public IGameObject
{
public:
	~Character() {};


	//初期位置を設定
	void SetSpownPos(const CVector3& pos) {
		m_SpownPosition = pos;
	}

	void Init(wchar_t* filePath, float radius, float hight, const CVector3& pos);

	virtual void Rotate() = 0;

	//回転量を設定
	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}

	//位置を取得
	const CVector3& GetPosition() {
		return m_Pos;
	}

	//ここで動く
	void Move(CVector3& move);
protected:
	SkinModelRender* m_Model = nullptr;			//敵のモデル
	CVector3 m_Pos = CVector3::Zero();			//敵の位置
	CQuaternion m_Rot = CQuaternion::Identity();//敵の回転
	CVector3 m_Scale = CVector3::One()*10.0f;	//敵の大きさ
	CharacterController m_CharaCon;				//キャラコン

	CVector3 m_MoveSpeed = CVector3::Zero();	//移動量
	CVector3 m_forward = CVector3::Front();		//前方向
	CVector3 m_SpownPosition = CVector3::Zero();//初期位置
};

