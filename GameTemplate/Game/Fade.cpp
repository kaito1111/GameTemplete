#include "pch.h"
#include "Fade.h"

bool Fade::Start()
{
	m_FadeSprite = NewGO<SpriteRender>(1);
	m_FadeSprite->Init(L"Brack.dds");
	m_FadeSprite->SetAlpha(m_Alpha);
	m_LodingSprite = NewGO<SpriteRender>(1);
	m_LodingSprite->Init(L"Loading.dds", 250.0f, 250.0f);
	m_LodingSprite->SetPosition(m_LodingSpritePos);
	return true;
}

void Fade::Update()
{
	const float MaxStayCount = 0.5f;
	//もしStayCountがMaxStayCountを超えていなければ
	if (m_StayCount >= MaxStayCount) {
		//透明度を下げる
		const float alhpaSub = 0.2f;
		m_Alpha -= alhpaSub;
	}
	else {
		//超えていれば上げる
		const float alphaAdd = 0.2f;
		m_Alpha += alphaAdd;
	}
	//もし透明ならStayCountを上げる
	if (m_Alpha > 1.1f) {
		m_StayCount+=gameTime().GetFrameDeltaTime();
		m_Alpha = 1.1f;
	}
	const float OneFrameLodingAngle = 6.0f;
	m_Angle += OneFrameLodingAngle;
	CQuaternion LoadingRot;
	LoadingRot.SetRotationDeg(CVector3::AxisZ(), m_Angle);
	m_LodingSprite->SetRotation(LoadingRot);
	m_LodingSprite->SetAlpha(m_Alpha);
	m_FadeSprite->SetAlpha(m_Alpha);
	//アルファ値がマイナスなので役目が終了
	if (m_Alpha < 0.0f) {
		DeleteGO(this);
	}
	//フェード中はゲームカメラも消す可能性があるから
	//こっちでもアップデートさせる
	g_camera3D.Update();
}

void Fade::OnDestroy()
{
	DeleteGO(m_FadeSprite);
	DeleteGO(m_LodingSprite);
}
