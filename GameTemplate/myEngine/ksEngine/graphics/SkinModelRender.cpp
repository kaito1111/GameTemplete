#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender() {

}

SkinModelRender::~SkinModelRender() {

}
void SkinModelRender::Init(const wchar_t * filePath, EnFbxUpAxis Up)
{
	wchar_t loadPath[256] = L"Assets/modelData/";
	wcscat(loadPath,filePath);
	m_SkinModel.Init(loadPath, Up);
}

void SkinModelRender::Update()
{
	
	m_SkinModel.UpdateWorldMatrix(m_Pos, m_Rot, m_Scale);
}

void SkinModelRender::Draw()
{
 	if (m_IsDraw) {
		//m_Skin.SetRenderMode(1);
		//m_Skin.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
		m_SkinModel.SetRenderMode(m_RenderMode);
		m_SkinModel.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}
