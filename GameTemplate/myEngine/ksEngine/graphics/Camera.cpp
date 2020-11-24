#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。
Camera g_camera2D;

void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	CMatrix viewMatrixInv = CMatrix::Identity();
	viewMatrixInv.Inverse(m_viewMatrix);
	m_Forward = { viewMatrixInv.m[2][0],viewMatrixInv.m[2][1],viewMatrixInv.m[2][2] };
	m_Right = { viewMatrixInv.m[0][0],viewMatrixInv.m[0][1],viewMatrixInv.m[0][2] };
	//プロジェクション行列を計算。
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//画角。
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
		m_near,
		m_far
	);
	m_OrtProjMatrix.MakeOrthoProjectionMatrix(
		m_wide,
		m_hight,
		m_near,
		m_far
	);
}