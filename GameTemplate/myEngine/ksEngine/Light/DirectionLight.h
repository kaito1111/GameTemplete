#pragma once
#include "LightBase.h"
#include "Light.h"
class DirectionLight : public LightBace
{
public :
	DirectionLight() {
		m_light.color = CVector4::White();
		m_light.direction = CVector3::Down();
		m_light.eyePos = CVector3::Front();
		m_light.pow = 0.5f;
	};
	~DirectionLight()
	{

	}
	void SetDirection(const CVector3& dir) {
		m_light.direction = dir;
	}

	void SetColor(const CVector3& color) {
		m_light.color = color;
	}
	SDirectionLight	GetRawData()const {
		return m_light;
	}

	void SetEyePos(const CVector3& eyePos) {
		m_light.eyePos = eyePos;
	}

	void SetSpecPow(float pow) {
		m_light.pow = pow;
	}
private:
	SDirectionLight m_light;
};

