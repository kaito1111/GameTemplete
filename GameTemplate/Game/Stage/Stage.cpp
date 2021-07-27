#include "Stage.h"
#include "Stage/Floor.h"
#include "Stage/Wall.h"
#include "PhysicsStageObject.h"
#include "SceneChangeLocation.h"
#include "ReturnLocation.h"
#include "candle.h"
#include "Torch.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

bool Stage::Start()
{
	//m_Model = NewGO<SkinModelRender>(0);
	//m_Model->Init(L"Assets/modelData/floor.cmo");
	//m_Model->SetScale(m_Scale);
	//m_Model->SetRenderMode(0);
		//Floor* floor = NewGO<Floor>(0);
		//floor->SetPosition(funclevel.position);
	//m_phy.CreateMeshObject(m_Model->GetModel(), m_pos, CQuaternion::Identity());
	//m_level.Init(m_LevelFilePath, [&](LevelObjectData funclevel)->bool {


	//	//Wall* wall = NewGO<Wall>(0);
	//	//wall->SetPosition(funclevel.position);

	//	if (wcscmp(funclevel.name, L"keleton")==0) {			
	//		m_SpownEnemyPosition = funclevel.position;
	//		return true;
	//	}
	//	if (wcscmp(funclevel.name, L"Player")==0) {
	//		m_SpownPlayerPosition = funclevel.position;
	//		return true;
	//	}

	//	PhysicsStageObject* PSO = NewGO<PhysicsStageObject>(0);
	//	PSO->SetObjectName(funclevel.name);
	//	PSO->SetPosition(funclevel.position);
	//	PSO->SetRotation(funclevel.rotation);
	//	return true;
	//});
	return true;
}

void Stage::Update()
{
	//m_Model->SetPosition(m_pos);
}

void Stage::OnDestroy()
{
	for (PhysicsStageObject* it : m_PSOList) {
		DeleteGO(it);
	}
	if (m_sky != nullptr) {
		DeleteGO(m_sky);
	}
	if (m_SCLoc.size() != 0) {
		for (auto& scl : m_SCLoc) {
			DeleteGO(scl);
		}
	}
	if (m_RCLoc.size() != 0) {
		for (auto& rcl : m_RCLoc) {
			DeleteGO(rcl);
		}
	}
	if (m_Can.size()!=0)
	{
		for (auto& can : m_Can) {
			DeleteGO(can);
		}
	}
	if (m_Torch.size() != 0)
	{
		for (auto& tor : m_Torch) {
			DeleteGO(tor);
		}
	}
}

void Stage::Load(wchar_t * filePath)
{
	wcscpy(m_LevelFilePath, filePath);	
	m_level.Init(m_LevelFilePath, [&](LevelObjectData funclevel)->bool {
		//Wall* wall = NewGO<Wall>(0);
		//wall->SetPosition(funclevel.position);

		if (wcscmp(funclevel.name, L"Skeleton") == 0) {
			return true;
		}
		if (wcscmp(funclevel.name, L"Archer") == 0) {
			return true;
		}
		if (wcscmp(funclevel.name, L"Player") == 0) {
			m_SpownPlayerPosition = funclevel.position;
			m_PlayerSpawnRot = funclevel.rotation;
			return true;
		}
		if (wcscmp(funclevel.name, L"Sky") == 0) {
			m_sky = NewGO<Sky>(0, "sky");
			m_sky->SetPosition(funclevel.position);
			return true;
		}
		if (wcscmp(funclevel.name, L"Boss") == 0) {
			return true;
		}

		if (wcscmp(funclevel.name, L"DebugShere")==0) {
			SceneChangeLocation* scl= NewGO<SceneChangeLocation>(0,"scl");
			scl->SetPosition(funclevel.position);
			scl->SetFilePath(m_LevelFilePath);
			m_SCLoc.push_back(scl);
			return true;
		}

		if (wcscmp(funclevel.name, L"ReturnRoad") == 0) {
			ReturnLocatoin* rcl= NewGO<ReturnLocatoin>(0,"rcl");
			m_RCLoc.push_back(rcl);
			rcl->SetPosition(funclevel.position);
			rcl->SetFilePath(m_LevelFilePath);
			return true;
		}

		if(wcscmp(funclevel.name, L"candle") == 0) {
			Candle* can = NewGO<Candle>(0, "candle");
			can->SetPosition(funclevel.position);
			can->SetRotation(funclevel.rotation);
			m_Can.push_back(can);
			return true;
		}
		if (wcscmp(funclevel.name, L"TitlePos") == 0) {
			m_TitlePos = funclevel.position;
			return true;
		}
		if (wcscmp(funclevel.name, L"Torch") == 0) {
			Torch* to = NewGO<Torch>(0, "candle");
			to->SetPosition(funclevel.position);
			m_Torch.push_back(to);
			return true;
		}

		if (wcscmp(funclevel.name, L"CameraPos") == 0) {
			m_TitleCameraPos = funclevel.position;
			return true;
		}	

		if (wcscmp(funclevel.name, L"CameraTarget") == 0) {
			m_TitleCameraTarget = funclevel.position;
			return true;
		}

		if (wcscmp(funclevel.name, L"CampFire") == 0) {
			return true;
		}
		PhysicsStageObject* PSO = NewGO<PhysicsStageObject>(0,"PSO");
		PSO->SetObjectName(funclevel.name);
		PSO->SetPosition(funclevel.position);
		PSO->SetRotation(funclevel.rotation);
		m_PSOList.push_back(PSO);
		return true;
	});
}
