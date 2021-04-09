#include "Stage.h"
#include "Stage/Floor.h"
#include "Stage/Wall.h"
#include "PhysicsStageObject.h"
#include "SceneChangeLocation.h"
#include "ReturnLocation.h"

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
}

void Stage::Load(wchar_t * filePath)
{
	wcscpy(m_LevelFilePath, filePath);	
	m_level.Init(m_LevelFilePath, [&](LevelObjectData funclevel)->bool {
		//Wall* wall = NewGO<Wall>(0);
		//wall->SetPosition(funclevel.position);

		if (wcscmp(funclevel.name, L"keleton") == 0) {
			return true;
		}
		if (wcscmp(funclevel.name, L"Archer") == 0) {
			return true;
		}
		if (wcscmp(funclevel.name, L"Player") == 0) {
			m_SpownPlayerPosition = funclevel.position;
			return true;
		}

		if (wcscmp(funclevel.name, L"Boss") == 0) {
			return true;
		}

		if (wcscmp(funclevel.name, L"DebugShere")==0) {
			SceneChangeLocation* SCLoc = NewGO<SceneChangeLocation>(0);
			SCLoc->SetPosition(funclevel.position);
			SCLoc->SetFilePath(m_LevelFilePath);
			return true;
		}

		if (wcscmp(funclevel.name, L"ReturnRoad") == 0) {
			ReturnLocatoin* SCLoc = NewGO<ReturnLocatoin>(0);
			SCLoc->SetPosition(funclevel.position);
			SCLoc->SetFilePath(m_LevelFilePath);
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
