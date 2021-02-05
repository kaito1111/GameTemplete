#include "pch.h"
#include "system/system.h"
#include "Game.h"
#include "level/Level.h"
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SampleSprite.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f,100.0f,500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	g_camera2D.SetPosition({ 0.0f, 0.0f, 500.0f });
	g_camera2D.Update();
	CGameObjectManager()->Init();
	//Sprite sprite;
	//sprite.Init(L"Assets/sprite/discode_icon.dds"/*, 128, 128*/);
	Game* game = NewGO<Game>(0);


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
		g_physics.GetDynamicWorld()->debugDrawWorld();
		//CQuaternion Rot = CQuaternion::Identity();
		//Rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
		//sprite.Update(/*CVector3::Zero(), CQuaternion::Identity(), CVector3::One()*/);
		//sprite.Draw(g_camera2D.GetViewMatrix(),g_camera2D.GetProjectionMatrix());

		CGameObjectManager()->ExcuteGame();

		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}