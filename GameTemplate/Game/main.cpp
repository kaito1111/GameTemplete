#include "pch.h"
#include "system/system.h"
#include "Game.h"
#include "Player/HuntedSprite.h"
#include "Fade.h"
#include "sound/SoundEngine.h"
#include "Title/Title.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 500.0f,300.0f,-200.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0, 0.0f });
	g_camera3D.SetFar(20000.0f);

	g_camera2D.SetPosition({ 0.0f, 0.0f, 500.0f });
	g_camera2D.Update();
	CGameObjectManager()->Init();

	//Sprite sprite;
	//sprite.Init(L"Assets/sprite/discode_icon.dds"/*, 128, 128*/);

	//::EffekseerRenderer::Renderer* effectRenderer = ::EffekseerRendererDX11::Renderer::Create(
	//	g_graphicsEngine->GetD3DDevice(),
	//	g_graphicsEngine->GetD3DDeviceContext(),
	//	512
	//);
	//::Effekseer::Manager* effectManager = ::Effekseer::Manager::Create(512);

	//Effekseer::Effect* effect = Effekseer::Effect::Create(effectManager, (EFK_CHAR*)L"Assets/effect/ItemPoint.efk");
	//Effekseer::Handle handle = effectManager->Play(effect, 0.0f, 0.0f, 0.0f);
	SoundEngine soundEngine;
	//�T�E���h�G���W�����������B
	soundEngine.Init();
	

	Title* title = NewGO<Title>(0,"title");
	//Game* game = NewGO<Game>(0, "game");
	//game->SetLevelFilePath(L"StageBoss.tkl");
	//HuntedSprite* huntSp = NewGO<HuntedSprite>(0);
	//SkinModelRender* testmodel = NewGO<SkinModelRender>(0);
	//testmodel->Init(L"Player.cmo");
	LightManager::GetInstance()->Start();
	Stopwatch m_sw;
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		m_sw.Start();
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		g_physics.GetDynamicWorld()->debugDrawWorld();
		//CQuaternion Rot = CQuaternion::Identity();
		//Rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
		//sprite.Update(/*CVector3::Zero(), CQuaternion::Identity(), CVector3::One()*/);
		//sprite.Draw(g_camera2D.GetViewMatrix(),g_camera2D.GetProjectionMatrix());
		//g_camera2D.Update();
		//g_camera3D.Update();
		CGameObjectManager()->ExcuteGame();
		//�T�E���h�G���W�����X�V�B
		soundEngine.Update();
		LightManager::GetInstance()->Update();
		//�G�t�F�N�g���X�V�B
		g_graphicsEngine->GetEffectEngine().Update();
		//effectRenderer->SetProjectionMatrix()

		//�`��I���B
		g_graphicsEngine->EndRender();

		m_sw.Stop();
		gameTime().PushDeltaFrameTime((float)m_sw.GetElased());
		char fpsText[256];
		sprintf(fpsText, "deltaTime = %f\n", m_sw.GetElapesedMillsecond());
		OutputDebugStringA(fpsText);
	}
}