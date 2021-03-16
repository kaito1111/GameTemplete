#pragma once
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"
class PhysicsStageObject;
class Player;
class Stage :public IGameObject
{
	//敵のポジションとローテーションを記憶
	struct EnemyInfor {
		CVector3 position = CVector3::Zero();
		CQuaternion rotation = CQuaternion::Identity();
	};
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void OnDestroy()override;

	void Load(wchar_t* filePath);
	CVector3 GetPlayerPos() {
		return m_SpownPlayerPosition;
	}
	CVector3 GetEnemyPos() {
		return m_SpownEnemyPosition;
	}
	//敵の情報を渡す(コピーではない)
	std::vector<EnemyInfor> GetEnemyInfor() {
		return m_EnemyList;
	}
private:
	//敵は複数出ることが多いのでリスト化
	std::vector<EnemyInfor> m_EnemyList;
	std::vector< PhysicsStageObject*> PSOList;
	//SkinModelRender* m_Model = nullptr;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_Scale = CVector3::One()*20.0f;
	//PhysicsStaticObject m_phy;
	Level m_level;
	wchar_t m_LevelFilePath[256] = {};
	CVector3 m_SpownPlayerPosition = CVector3::Zero();
	CVector3 m_SpownEnemyPosition = CVector3::Zero();
};

