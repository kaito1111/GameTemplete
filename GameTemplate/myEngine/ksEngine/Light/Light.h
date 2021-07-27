#pragma once
#include "stdafx.h"
struct SPointLight {
	CVector3	position;			//!<位置。
	float pad0;
	CVector3	positionInView;		//!<ビュー空間での座標。
	float pad1;
	CVector4	color;				//!<ライトのカラー。
	CVector4	attn;				//!<減衰定数。xはポイントライトの影響が届く範囲。yはポイントライトの減衰率に影響を与えます。
									//!<yが大きくなると、減衰が強くなります。1.0で線形の減衰率になります。z,wは未使用。
};

/*!
 *@brief	ディレクションライト。
 */
struct SDirectionLight {
	CVector4	color;			//!<ライトのカラー。
	CVector3	direction;		//!<ライトの方向。
	float pad;
	CVector3	eyePos;
	float pow;
};