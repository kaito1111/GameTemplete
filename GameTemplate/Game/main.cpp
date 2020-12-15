#include "pch.h"
#include "system/system.h"
#include "Game.h"
#include "level/Level.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f,100.0f,500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	g_camera2D.SetPosition({ 0.0f, 0.0f, 500.0f });

	CGameObjectManager()->Init();

	SpriteRender* m_Sprite = NewGO<SpriteRender>(0);
	m_Sprite->Init(L"Assets/sprite/reticle.dds");
	//Game* game = NewGO<Game>(0);
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
		g_physics.GetDynamicWorld()->debugDrawWorld();

		CGameObjectManager()->ExcuteGame();



		//描画終了。
		g_graphicsEngine->EndRender();
	}
}