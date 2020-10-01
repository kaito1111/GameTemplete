#include "pch.h"
#include "system/system.h"
#include "Player.h"
#include "Player2.h"
#include "Stage.h"
#include "level/Level.h"
#include "GameObjectManager.h"
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	//プレイヤー
	Player player[4];
	//Player2 player2;
	//Stage stage;
	ksEngine::GameObjectManager* GM = ksEngine::GameObjectManager::GetInstance();
	//GM->Init();
	GM->AddGameObjectManager(0,player[0]);
	GM->DeleteGameObjectManager(player[0]);
	//GM->AddGameObjectManager(&player[1]);
	//GM->AddGameObjectManager(&player[2]);
	//GM->AddGameObjectManager(&player[3]);
	//GM->AddGameObjectManager(&player2);
	//GM->AddGameObjectManager(&stage);
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		
		GM->ExcuteMain();
		GM->ExcuteGame();
		//カメラの更新。
		g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}