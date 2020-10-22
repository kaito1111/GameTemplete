#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

bool Stage::Start()
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/stage.cmo");
	m_phy.CreateMeshObject(m_Model->GetModel(), m_pos, CQuaternion::Identity());
	return true;
}

void Stage::Update()
{
}