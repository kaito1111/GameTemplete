#pragma once
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"
class PhysicsStageObject;
class Player;
class SceneChangeLocation;
class ReturnLocatoin;
class Candle;
class Torch;
class Stage final :public IGameObject
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
	CVector3 GetPlayerPos()const {
		return m_SpownPlayerPosition;
	}
	
	CQuaternion GetPlayerRotation() const{
		return m_PlayerSpawnRot;
	}

	CVector3 GetEnemyPos()const {
		return m_SpownEnemyPosition;
	}

	CVector3 GetTitlePos() const{
		return m_TitlePos;
	}
	CVector3 GetTitleCameraPos() const{
		return m_TitleCameraPos;
	}
	CVector3 GetTitleCameraTarget()const {
		return m_TitleCameraTarget;
	}
private:
	std::vector< PhysicsStageObject*> m_PSOList;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_Scale = CVector3::One()*20.0f;
	Level m_level;
	wchar_t m_LevelFilePath[256] = {};
	CVector3 m_SpownPlayerPosition = CVector3::Zero();
	CQuaternion m_PlayerSpawnRot = CQuaternion::Identity();
	CVector3 m_SpownEnemyPosition = CVector3::Zero();
	Sky* m_sky = nullptr;
	CVector3 m_TitlePos = CVector3::Zero();
	CVector3 m_TitleCameraPos = CVector3::Zero();
	CVector3 m_TitleCameraTarget = CVector3::Zero();
	std::vector<SceneChangeLocation*> m_SCLoc;
	std::vector<ReturnLocatoin*> m_RCLoc;
	std::vector<Candle*> m_Can;
	std::vector<Torch*> m_Torch;
};

