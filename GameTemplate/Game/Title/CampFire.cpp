#include "pch.h"
#include "CampFire.h"

namespace {
	const float EffectScale = 2.0f;
}
bool CampFire::Start()
{
	m_PointLight = NewGO<PointLight>(0,"pointlight");

	CVector3 LightPos = m_Position;
	LightPos.y += 10.0f;
	m_PointLight->SetPosition(LightPos);
	m_PointLight->SetColor({ 10.0f,5.0f,2.0f,1.0f });
	float LightPower = 250.0f;
	m_PointLight->SetRenge({ LightPower,2.5f,0.0f,0.0f });
	//m_PointLight2 =	NewGO<PointLight>(0, "pointlight");
	//m_PointLight2->SetColor(CVector4::White()*0.5);
	//m_PointLight2->SetPosition(LightPos);
	//LightPower = 100.0f;
	//m_PointLight2->SetRenge({ LightPower,2.5f,0.0f,0.0f });

	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"CampFire.cmo");
	m_Model->SetDraw(true);

	m_effect = NewGO<Effect>(0);
	if (!m_effect->IsPlay()) {
		m_effect->Play(L"Assets/effect/Fire.efk");
		m_effect->SetPosition(m_Position);
		m_Position.z += 50.0f;
		m_effect->SetScale(CVector3::One()*EffectScale);
	}
	m_Sound.Init(L"FireCamp.wav");
	m_Sound.SetVolume(1.0f);
	m_Sound.Play(true);
	return true; 
}

void CampFire::Update()
{
	m_ScaleTime += gameTime().GetFrameDeltaTime() * 1.0f;
	//if (m_ScaleTime > 5.0f) {
		//if (m_LightPower > 300.0f ||
		//	m_LightPower < 170.0f) {
		//	a *= -1.0f;
		//}
	//}
	//else if (m_ScaleTime < 5.0f) {
	//	if (m_LightPower > 150.0f ||
	//		m_LightPower < 100.0f) {
	//		a *= -1.0f;
	//	}
	//}
	//if (m_ScaleTime <= 5.0f&&
	//	m_Big == false) {
	//	m_LightPower = 150.0f;
	//	m_Big = true;
	//}
	//m_LightPower += a;
	////if (m_ScaleTime > 5.0f) {
	////	if (m_LightPower2 > 250.0f ||
	////		m_LightPower2 < 200.0f) {
	////		a2 *= -1.0f;
	////	}
	////}
	////else if (m_ScaleTime < 5.0f) {
	////	if (m_LightPower2 > 150.0f ||
	////		m_LightPower2 < 50.0f) {
	////		a2 *= -1.0f;
	////	}
	////}
	//if (m_ScaleTime > 10.0f) {
	//	m_ScaleTime = 0.0f;
	//	m_LightPower = 100.0f;
	//	m_Big = false;
	//}
	//m_LightPower2 += a2;
	if (m_ScaleTime > m_lightPowArraySize)
	{
		m_ScaleTime -= static_cast<float>(m_lightPowArraySize);
	}

	m_currentLigPowNum = static_cast<int>(m_ScaleTime);
	m_currentLigPowNum = m_currentLigPowNum % m_lightPowArraySize;
	int nextLigPowNum = (m_currentLigPowNum + 1) % m_lightPowArraySize;
	float ligPowWeight = m_ScaleTime - m_currentLigPowNum;

	m_LightPower = (m_lightPowArray[m_currentLigPowNum] * (1.0f - ligPowWeight)) + (m_lightPowArray[nextLigPowNum] * ligPowWeight);

	m_PointLight->SetRenge({ m_LightPower,2.5f,0.0f,0.0f });
	//m_PointLight2->SetRenge({ m_LightPower2,2.5f,0.0f,0.0f });
	m_effect->SetScale((CVector3::One()*EffectScale)*(m_LightPower / GetMaxLightPow()));
}

void CampFire::OnDestroy()
{
	DeleteGO(m_PointLight);
	DeleteGO(m_Model);
	DeleteGO(m_PointLight2);
	DeleteGO(m_effect);
}
