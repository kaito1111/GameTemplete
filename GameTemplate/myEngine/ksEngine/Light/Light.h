#pragma once
#include "stdafx.h"
struct SPointLight {
	CVector3	position;			//!<�ʒu�B
	float pad0;
	CVector3	positionInView;		//!<�r���[��Ԃł̍��W�B
	float pad1;
	CVector4	color;				//!<���C�g�̃J���[�B
	CVector4	attn;				//!<�����萔�Bx�̓|�C���g���C�g�̉e�����͂��͈́By�̓|�C���g���C�g�̌������ɉe����^���܂��B
									//!<y���傫���Ȃ�ƁA�����������Ȃ�܂��B1.0�Ő��`�̌������ɂȂ�܂��Bz,w�͖��g�p�B
};

/*!
 *@brief	�f�B���N�V�������C�g�B
 */
struct SDirectionLight {
	CVector4	color;			//!<���C�g�̃J���[�B
	CVector3	direction;		//!<���C�g�̕����B
	float pad;
	CVector3	eyePos;
	float pow;
};