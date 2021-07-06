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
	*@brief ���f�[�^�̎擾�B
	*/
	SPointLight& GetRawData()
	{
		return m_Light;
	}
private:
	CVector3	m_Position;			//!<�ʒu�B
	CVector3	m_PositionInView;		//!<�r���[��Ԃł̍��W�B
	CVector4	m_Color;				//!<���C�g�̃J���[�B
	CVector4	m_Attn;				//!<�����萔�Bx�̓|�C���g���C�g�̉e�����͂��͈́By�̓|�C���g���C�g�̌������ɉe����^���܂��B
										//!<y���傫���Ȃ�ƁA�����������Ȃ�܂��B1.0�Ő��`�̌������ɂȂ�܂��Bz,w�͖��g�p�B
	SPointLight	m_Light;
};

