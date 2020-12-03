#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender() {

}

SkinModelRender::~SkinModelRender() {

}
void SkinModelRender::Init(const wchar_t * filePath, EnFbxUpAxis Up)
{

	m_Skin.Init(filePath, Up);
}

void SkinModelRender::Update()
{
	
	m_Skin.UpdateWorldMatrix(m_Pos, m_Rot, m_Scale);
}

void SkinModelRender::Draw()
{
 	if (m_IsDraw) {
		//m_Skin.SetRenderMode(1);
		//m_Skin.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
		m_Skin.SetRenderMode(0);
		m_Skin.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}
