#include "pch.h"
#include "system/system.h"
#include "Player.h"
#include "Player2.h"
#include "Stage.h"
#include "level/Level.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 0.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	CGameObjectManager()->Init();

	Player*m_player = NewGO<Player>(0);

	SkinModelRender* m_unity = NewGO<SkinModelRender>(0);
	m_unity->Init(L"Assets/modelData/unityChan.cmo");

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//g_physics.
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		g_physics.GetDynamicWorld()->debugDrawWorld();
		//カメラの更新。
		g_camera3D.Update();
		CGameObjectManager()->ExcuteMain();
		CGameObjectManager()->ExcuteGame();




		//描画終了。
		g_graphicsEngine->EndRender();
	}
}