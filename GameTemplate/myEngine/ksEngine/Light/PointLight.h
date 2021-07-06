#pragma once
#include "LightBase.h"
#include "Light.h"
class PointLight : public LightBace
{
public:
	PointLight() {};
	~PointLight() {};

	void SetPosition(const CVector3& pos) {
		m_Position = pos;
		m_Light.position = pos;
	}

	void SetColor(const CVector4& color) {
		m_Color = color;
		m_Light.color = color;
	}

	void SetRenge(const CVector4& ran) {
		m_Attn = ran;
		m_Light.attn = ran;
	}
	/*!
	*@brief 生データの取得。
	*/
	SPointLight& GetRawData()
	{
		return m_Light;
	}
private:
	CVector3	m_Position;			//!<位置。
	CVector3	m_PositionInView;		//!<ビュー空間での座標。
	CVector4	m_Color;				//!<ライトのカラー。
	CVector4	m_Attn;				//!<減衰定数。xはポイントライトの影響が届く範囲。yはポイントライトの減衰率に影響を与えます。
										//!<yが大きくなると、減衰が強くなります。1.0で線形の減衰率になります。z,wは未使用。
	SPointLight	m_Light;
};

