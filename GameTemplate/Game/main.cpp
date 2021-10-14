#include "pch.h"
#include "system/system.h"
#include "Game.h"
#include "Player/HuntedSprite.h"
#include "Fade.h"
#include "sound/SoundEngine.h"
#include "Title/Title.h"
#include "GameCamera.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 500.0f,300.0f,-200.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0, 0.0f });
	g_camera3D.SetFar(20000.0f);

	g_camera2D.SetPosition({ 0.0f, 0.0f, 500.0f });
	g_camera2D.Update();
	//ゲームオブジェクトマネージャーを初期化
	CGameObjectManager()->Init();

	SoundEngine soundEngine;
	//サウンドエンジンを初期化。
	soundEngine.Init();
	
	Title* title = NewGO<Title>(0,"title");
	//Game* game = NewGO<Game>(0, "game");
	//game->SetLevelFilePath(L"StageBoss.tkl");
	//ライトの初期化
	LightManager::GetInstance()->Start();
	//ゲームタイマー
	Stopwatch m_sw;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		m_sw.Start();
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		g_physics.GetDynamicWorld()->debugDrawWorld();
		//ゲームオブジェクトを更新
		CGameObjectManager()->ExcuteGame();

		//サウンドエンジンを更新。
		soundEngine.Update();
		LightManager::GetInstance()->Update();
		//エフェクトを更新。
		g_graphicsEngine->GetEffectEngine().Update();

		//描画終了。
		g_graphicsEngine->EndRender();

		//スピンロックを行う。
		int restTime = 0;
		do {
			m_sw.Stop();
			restTime = 32 - (int)m_sw.GetElapesedMillsecond();
		} while (restTime > 0);


		m_sw.Stop();
		// スピンロック

		gameTime().PushDeltaFrameTime((float)m_sw.GetElased());
		/*char fpsText[256];
		sprintf(fpsText, "deltaTime = %f\n", m_sw.GetElapesedMillsecond());
		OutputDebugStringA(fpsText);*/
	}
}