#include "pch.h"
#include "Stage/Floor.h"

bool Floor::Start()
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Assets/modelData/Stage2Gate.cmo");
	return true;
}

void Floor::Update()
{
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Model->SetScale(m_Scale);
}
