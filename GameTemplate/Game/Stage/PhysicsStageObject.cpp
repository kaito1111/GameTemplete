#include "pch.h"
#include "PhysicsStageObject.h"

bool PhysicsStageObject::Start() {
	m_Model = NewGO<SkinModelRender>(0);
	wchar_t filePath[256] = {};
	wcscat(filePath, m_ObjectName);
	wcscat(filePath, L".cmo");
	m_Model->Init(filePath);
	m_Model->SetPosition(m_Pos);
	m_Model->SetRotation(m_Rot);
	m_Pysics.CreateMeshObject(m_Model->GetModel(), m_Pos, m_Rot);
	return true;
}

void PhysicsStageObject::OnDestroy()
{
	DeleteGO(m_Model);
}
