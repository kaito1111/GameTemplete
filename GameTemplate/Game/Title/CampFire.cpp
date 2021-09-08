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
	m_effect->SetScale((CVector3::One()*EffectScale)*(m_LightPower / GetMaxLightPow()));
}

void CampFire::OnDestroy()
{
	DeleteGO(m_PointLight);
	DeleteGO(m_Model);
	DeleteGO(m_effect);
}
