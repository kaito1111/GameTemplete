#include "stdafx.h"
#include "GameObjectManager.h"
namespace ksEngine {

	GameObjectManager::GameObjectManager()
	{
	}

	GameObjectManager::~GameObjectManager()
	{
	}

	void GameObjectManager::Start()
	{
		for (GameObjectList GOList : m_GameObjectListArray) {
			for (IGameObject* GO : GOList) {
				GO->StartWrapper();
			}
		}
	}

	void GameObjectManager::Update()
	{
		g_graphicsEngine->GetShadowMap()->UpdateShadowMap();
		for (GameObjectList GOList : m_GameObjectListArray)
			for (IGameObject* GO : GOList) {
				GO->UpdateWrapper();
		}
	}

	void GameObjectManager::Draw()
	{
		//物理ワールドのデバッグ描画。
		g_physics.DebubDrawWorld(); 
		g_graphicsEngine->GetShadowMap()->RenderToShadowMap();
		for (GameObjectList GOList : m_GameObjectListArray) {
			for (IGameObject* GO : GOList) {
				GO->DrawWrapper();
			}
		}
	}

	void GameObjectManager::PostRender()
	{
		for (GameObjectList GOList : m_GameObjectListArray) {
			for (IGameObject* GO : GOList) {
				GO->PostRenderWrapper();
			}
		}
	}

	void GameObjectManager::ExecuteDeleteGameObject()
	{
		int PreBufferNo = m_currentDeleteObjectBufferNo;
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for (GameObjectList& GOList : m_deleteObjectArray[PreBufferNo]) {
			for (IGameObject* go : GOList) {
				GameObjectPrio prio = go->GetPriority();
				GameObjectList& goExecList = m_GameObjectListArray[prio];

				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) {
					(*it)->m_IsRegistDeadList = false;
					goExecList.erase(it);
				}
			}
			GOList.clear();
		}
	}

	void GameObjectManager::ExcuteGame()
	{
		Start();
		Update();
		Draw();
		PostRender();
		ExecuteDeleteGameObject();
	}

	void GameObjectManager::Init()
	{
		m_GameObjectListArray.resize(m_gameObjectPriorityMax);
		m_deleteObjectArray[0].resize(m_gameObjectPriorityMax);
		m_deleteObjectArray[1].resize(m_gameObjectPriorityMax);
	}
}