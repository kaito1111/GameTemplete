#include "stdafx.h"

void SpriteRender::Init(const wchar_t * fileName, bool is3DDraw)
{
	m_sprite.Init(fileName/*, 128, 128*/);
	m_Is3DDraw = is3DDraw;
}

void SpriteRender::Update()
{
	m_sprite.SetPosition(m_Pos);
	m_sprite.SetRotation(m_Rot);
	m_sprite.SetScale(m_Scale);
	m_sprite.Update(/*m_Pos, m_Rot, m_Scale*/);
}

void SpriteRender::Draw() 
{
	if (m_Is3DDraw) {
		m_sprite.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}

void SpriteRender::PostRender()
{
	if (!m_Is3DDraw) {
		m_sprite.Draw(
			g_camera2D.GetViewMatrix(),
			g_camera2D.GetOrthoProjectionMatrix()
		);
	}

}
