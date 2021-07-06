#include "pch.h"
#include "candle.h"

bool Candle::Start()
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"candle.cmo");
	m_Model->SetPosition(m_Position);
	m_Model->SetRotation(m_Rotation);

	m_PointLightRed =NewGO<PointLight>(0,"pointLight");
	CVector3 LightPos = m_Position;
	LightPos.y += 50.0f;
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rotation);
	CVector3 Forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	Forward.Normalize();
	LightPos += Forward * -50.0f;
	m_PointLightRed->SetPosition(LightPos);
	m_PointLightRed->SetColor({ 4.0f,2.0f,1.0f,1.0f });

	m_PointLightRed->SetRenge({ m_LightPower,2.5f,0.0f,0.0f });

	m_PointLightYellow = NewGO<PointLight>(0);
	m_PointLightYellow->SetPosition(LightPos);
	m_PointLightYellow->SetColor({ 5.0f,5.0f,2.0f,1.0f });
	float m_LightPower = 60.0f;
	m_PointLightYellow->SetRenge({ m_LightPower,2.5f,0.0f,0.0f });
	//g_graphicsEngine->GetShadowMap()->SetLightCameraPosition(m_Position);
	return true;
}

void Candle::Update()
{
	if (m_LightPower > 200.0f || m_LightPower < 190.0f) {
		a *= -1.0f;
	}
	m_LightPower += a;
	m_PointLightRed->SetRenge({ m_LightPower,2.5f,0.0f,0.0f });
}
