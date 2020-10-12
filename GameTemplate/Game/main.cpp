#include "pch.h"
#include "system/system.h"
#include "Player.h"
#include "Player2.h"
#include "Stage.h"
#include "level/Level.h"
#include "graphics/2D/Sprite.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
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
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		CGameObjectManager()->ExcuteMain();
		CGameObjectManager()->ExcuteGame();


		sprite.Update();
		sprite.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());


		//�J�����̍X�V�B
		g_camera3D.Update();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}