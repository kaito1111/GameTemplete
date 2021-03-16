#include "stdafx.h"
#include "GameObjectManager.h"
namespace ksEngine {

	GameObjectManager::GameObjectManager()
	{
		//Effekseer�̏������֐��B
		//���̏������֐����A����i�ɒǉ��A���s�����Effekser�̏��������s����B
			//�����_���[���������B
		m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
			g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
			g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
			20000										//�|���̍ő吔�B
		);
		//�G�t�F�N�g�}�l�[�W�����������B
		m_effekseerManager = Effekseer::Manager::Create(10000);

		// �`��p�C���X�^���X����`��@�\��ݒ�
		m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
		m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
		m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
		m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
		m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

		// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
		m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
	}

	GameObjectManager::~GameObjectManager()
	{
		//�T�U�s�ڂ���U�Q�s�ڂ�Effekseer�̏I������
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
		//Effekseer�J�����s���ݒ�B
		//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseer���X�V�B
		m_effekseerManager->Update();
		for (GameObjectList GOList : m_GameObjectListArray)
			for (IGameObject* GO : GOList) {
				GO->UpdateWrapper();
			}
	}

	void GameObjectManager::Draw()
	{
		//�������[���h�̃f�o�b�O�`��B
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
		//�|�X�g�G�t�F�N�g�̕`��B
		PostEffect->Draw();
		PostEffect->PostRender();
		//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
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