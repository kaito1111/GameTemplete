#include "pch.h"
#include "candle.h"

namespace {
	const CVector4 LightColor = { 4.0f,2.0f,1.0f,1.0f };	//m_PointLightRedの色
	const CVector4 Light2Color = { 5.0f,5.0f,2.0f,1.0f };	//m_PointLightYellowの色
	const CVector3 EffectScale = CVector3::One()*0.1f;		//エフェクトの大きさ
	const float m_LightPower = 60.0f;						//ライトの強さ
	const float UpLight = 30.0f;							//ライトの高さをモデルにあわせる
	const float ForwardLight = -40.0f;						//ライトの位置をモデルにあわせる
	const float attn = 2.5f;								//減衰定数
	const float MaxLightPower = 200.0f;						//ライトの光の強さの最大
	const float MinLightPower = 190.0f;						//ライトの光の強さの最小
}
bool Candle::Start()
{
	//モデルを初期化
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"candle.cmo");
	m_Model->SetPosition(m_Position);
	m_Model->SetRotation(m_Rotation);

	//炎のポイントライトを初期化
	m_PointLightRed =NewGO<PointLight>(0,"pointLight");
	CVector3 LightPos = m_Position;
	LightPos.y+= UpLight;
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_Rotation);
	CVector3 Forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	Forward.Normalize();
	LightPos += Forward * ForwardLight;
	m_PointLightRed->SetPosition(LightPos);
	m_PointLightRed->SetColor(LightColor);
	m_PointLightRed->SetRenge({ m_LightPower,attn,0.0f,0.0f });

	//炎の外側のポイントライトを初期化
	m_PointLightYellow = NewGO<PointLight>(0);
	m_PointLightYellow->SetPosition(LightPos);
	m_PointLightYellow->SetColor(Light2Color);
	m_PointLightYellow->SetRenge({ m_LightPower,attn,0.0f,0.0f });

	//エフェクトを初期化
	m_Effect = NewGO<Effect>(0);
	m_Effect->Play(L"Assets/effect/Fire.efk");
	m_Effect->SetScale(EffectScale);
	m_Effect->SetPosition(LightPos);
	return true;
}

void Candle::Update()
{
	//炎に強弱をつける
	if (m_LightPower > MaxLightPower || m_LightPower < MinLightPower) {
		a *= -1.0f;
	}
	m_LightPower += a;
	m_PointLightRed->SetRenge({ m_LightPower,attn,0.0f,0.0f });
	m_Effect->SetScale(EffectScale*(m_LightPower / MaxLightPower));
}

void Candle::OnDestroy()
{
	//NewGOしたら消す
	DeleteGO(m_Model);
	DeleteGO(m_PointLightRed);
	DeleteGO(m_PointLightYellow);
	DeleteGO(m_Effect);
}
