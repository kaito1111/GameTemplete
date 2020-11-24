#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B
Camera g_camera2D;

void Camera::Update()
{
	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	CMatrix viewMatrixInv = CMatrix::Identity();
	viewMatrixInv.Inverse(m_viewMatrix);
	m_Forward = { viewMatrixInv.m[2][0],viewMatrixInv.m[2][1],viewMatrixInv.m[2][2] };
	m_Right = { viewMatrixInv.m[0][0],viewMatrixInv.m[0][1],viewMatrixInv.m[0][2] };
	//�v���W�F�N�V�����s����v�Z�B
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//��p�B
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//�A�X�y�N�g��B
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