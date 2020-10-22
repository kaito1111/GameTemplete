#include "pch.h"
#include "system/system.h"
#include "Player.h"
#include "Player2.h"
#include "Stage.h"
#include "level/Level.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 0.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	CGameObjectManager()->Init();

	Player*m_player = NewGO<Player>(0);

	SkinModelRender* m_unity = NewGO<SkinModelRender>(0);
	m_unity->Init(L"Assets/modelData/unityChan.cmo");

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//g_physics.
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		g_physics.GetDynamicWorld()->debugDrawWorld();
		//�J�����̍X�V�B
		g_camera3D.Update();
		CGameObjectManager()->ExcuteMain();
		CGameObjectManager()->ExcuteGame();




		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}