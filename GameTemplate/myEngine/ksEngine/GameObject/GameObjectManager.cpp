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
		//Effekseerカメラ行列を設定。
		//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		for (GameObjectList GOList : m_GameObjectListArray)
			for (IGameObject* GO : GOList) {
				GO->UpdateWrapper();
			}
	}

	void GameObjectManager::Draw()
	{
		//物理ワールドのデバッグ描画。
		g_physics.DebubDrawWorld();
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
					if ((*it)->IsNewFromGameObjectManager()) {
						delete (*it);
					}
					goExecList.erase(it);
				}
			}
			GOList.clear();
		}
	}

	void GameObjectManager::ExcuteGame()
	{
		auto PostEffect = g_graphicsEngine->GetPostEffect();
		auto ShadowMap = g_graphicsEngine->GetShadowMap();
		Start();
		Update();

		ShadowMap->RenderToShadowMap();

		PostEffect->ChangeMainRendertTarget();
		Draw();
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		g_graphicsEngine->GetEffectEngine().Render();
		PostRender();
		g_camera3D.Update();
		//ポストエフェクトの描画。
		PostEffect->Draw();
		PostEffect->PostRender();
		ExecuteDeleteGameObject();

	}

	void GameObjectManager::Init()
	{
		m_GameObjectListArray.resize(m_gameObjectPriorityMax);
		m_deleteObjectArray[0].resize(m_gameObjectPriorityMax);
		m_deleteObjectArray[1].resize(m_gameObjectPriorityMax);
	}
}