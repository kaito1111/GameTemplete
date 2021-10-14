#include "pch.h"
#include "system/system.h"
#include "Game.h"
#include "Player/HuntedSprite.h"
#include "Fade.h"
#include "sound/SoundEngine.h"
#include "Title/Title.h"
#include "GameCamera.h"

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
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[��������
	CGameObjectManager()->Init();

	SoundEngine soundEngine;
	//�T�E���h�G���W�����������B
	soundEngine.Init();
	
	Title* title = NewGO<Title>(0,"title");
	//Game* game = NewGO<Game>(0, "game");
	//game->SetLevelFilePath(L"StageBoss.tkl");
	//���C�g�̏�����
	LightManager::GetInstance()->Start();
	//�Q�[���^�C�}�[
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
		//�Q�[���I�u�W�F�N�g���X�V
		CGameObjectManager()->ExcuteGame();

		//�T�E���h�G���W�����X�V�B
		soundEngine.Update();
		LightManager::GetInstance()->Update();
		//�G�t�F�N�g���X�V�B
		g_graphicsEngine->GetEffectEngine().Update();

		//�`��I���B
		g_graphicsEngine->EndRender();

		//�X�s�����b�N���s���B
		int restTime = 0;
		do {
			m_sw.Stop();
			restTime = 32 - (int)m_sw.GetElapesedMillsecond();
		} while (restTime > 0);


		m_sw.Stop();
		// �X�s�����b�N

		gameTime().PushDeltaFrameTime((float)m_sw.GetElased());
		/*char fpsText[256];
		sprintf(fpsText, "deltaTime = %f\n", m_sw.GetElapesedMillsecond());
		OutputDebugStringA(fpsText);*/
	}
}