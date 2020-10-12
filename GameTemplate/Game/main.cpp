#include "pch.h"
#include "system/system.h"
#include "Player.h"
#include "Player2.h"
#include "Stage.h"
#include "level/Level.h"
#include "graphics/2D/Sprite.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 00.0f, -10.0f });
	g_camera3D.SetTarget({ 0.0f, 00.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	CGameObjectManager()->Init();
	
	Sprite sprite;
	sprite.Init(L"Assets/sprite/discode_icon.dds");
	//CQuaternion rot;
	//rot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	//sprite.SetRotation(rot);
	//IGameObjectPtr hoge = NewGO< PlayerHoge>(0);
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
		CGameObjectManager()->ExcuteMain();
		CGameObjectManager()->ExcuteGame();


		sprite.Update();
		sprite.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());


		//カメラの更新。
		g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}