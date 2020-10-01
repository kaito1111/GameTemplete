#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

bool Stage::Start()
{
	m_Model.Init(L"Assets/modelData/stage.cmo");
	return true;
}

void Stage::Update()
{
	m_Model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void Stage::Draw()
{
	m_Model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
