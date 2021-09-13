#include "pch.h"
#include "Torch.h"

namespace {
	const CVector3 effectScale = CVector3::One()*2.0f;
	const float UpLight = 135.0f;//ƒ‰ƒCƒg‚ÌˆÊ’u
}

bool Torch::Start()
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"Torch.cmo");
	m_Model->SetPosition(m_Position);

	CVector3 LightPosition = m_Position;
	LightPosition.y += UpLight;
	m_PoinsLight = NewGO<PointLight>(0, "pointLight");
	m_PoinsLight->SetPosition(LightPosition);

	m_PoinsLight->SetColor({ 4.0f,2.0f,1.0f,1.0f });

	m_PoinsLight->SetRenge({ m_LightPower,2.5f,0.0f,0.0f });
	m_Effect = NewGO<Effect>(0);
	m_Effect->Play(L"Assets/effect/Fire.efk");
	m_Effect->SetPosition(LightPosition);
	m_Effect->SetScale(effectScale);
	return true;
}

void Torch::Update()
{
	if (m_LightPower > 500.0f || m_LightPower < 450.0f) {
		m_LightMulPower *= -1.0f;
	}
	m_LightPower += m_LightMulPower;
	m_PoinsLight->SetRenge({ m_LightPower,2.5f,0.0f,0.0f });
	m_Effect->SetScale(effectScale*(m_LightPower / 500.0f));
}

void Torch::OnDestroy()
{
	DeleteGO(m_Model);
	DeleteGO(m_PoinsLight);
	DeleteGO(m_Effect);
}
