#include "stdafx.h"
#include "GameObjectManager.h"
namespace ksEngine {

	GameObjectManager::GameObjectManager()
	{
		//Effekseerの初期化関数。
		//この初期化関数を就活作品に追加、実行すればEffekserの初期化が行える。
			//レンダラーを初期化。
		m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
			g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
			g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
			20000										//板ポリの最大数。
		);
		//エフェクトマネージャを初期化。
		m_effekseerManager = Effekseer::Manager::Create(10000);

		// 描画用インスタンスから描画機能を設定
		m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
		m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
		m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
		m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
		m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

		// 描画用インスタンスからテクスチャの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
		m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
	}

	GameObjectManager::~GameObjectManager()
	{
		//５６行目から６２行目がEffekseerの終了処理
		if (m_effekseerManager != nullptr) {
			m_effekseerManager->Destroy();

		}
		if (m_effekseerRenderer != nullptr) {
			m_effekseerRenderer->Destroy();
		}
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
		//カメラ行列とプロジェクション行列を設定。
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseerを更新。
		m_effekseerManager->Update();
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
		PostRender();
		//ポストエフェクトの描画。
		PostEffect->Draw();
		PostEffect->PostRender();
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
		ExecuteDeleteGameObject();
	}

	void GameObjectManager::Init()
	{
		m_GameObjectListArray.resize(m_gameObjectPriorityMax);
		m_deleteObjectArray[0].resize(m_gameObjectPriorityMax);
		m_deleteObjectArray[1].resize(m_gameObjectPriorityMax);
	}
}