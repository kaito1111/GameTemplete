#include "pch.h"
#include "Wall.h"

bool Wall::Start()
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"wall.cmo");
	m_Pysics.CreateMeshObject(m_Model->GetModel(), m_Pos, m_Rot);
	return true;
}

void Wall::Update()
{
}
