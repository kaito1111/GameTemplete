#pragma once
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"
class PhysicsStageObject;
class Player;
class Enemy;
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
private:
	std::vector< PhysicsStageObject*> m_PSOList;
	//SkinModelRender* m_Model = nullptr;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_Scale = CVector3::One()*20.0f;
	//PhysicsStaticObject m_phy;
	Level m_level;
	wchar_t m_LevelFilePath[256] = {};
	CVector3 m_SpownPlayerPosition = CVector3::Zero();
	CVector3 m_SpownEnemyPosition = CVector3::Zero();
	std::vector< Enemy*> m_EnemyVector;
};

