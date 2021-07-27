#include "pch.h"
#include "candle.h"

namespace {
	const CVector4 LightColor = { 4.0f,2.0f,1.0f,1.0f };	//m_PointLightRed�̐F
	const CVector4 Light2Color = { 5.0f,5.0f,2.0f,1.0f };	//m_PointLightYellow�̐F
	const CVector3 EffectScale = CVector3::One()*0.1f;		//�G�t�F�N�g�̑傫��
	const float m_LightPower = 60.0f;						//���C�g�̋���
	const float UpLight = 30.0f;							//���C�g�̍��������f���ɂ��킹��
	const float ForwardLight = -40.0f;						//���C�g�̈ʒu�����f���ɂ��킹��
	const float attn = 2.5f;								//�����萔
	const float MaxLightPower = 200.0f;						//���C�g�̌��̋����̍ő�
	const float MinLightPower = 190.0f;						//���C�g�̌��̋����̍ŏ�
}
bool Candle::Start()
{
	//���f����������
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(L"candle.cmo");
	m_Model->SetPosition(m_Position);
	m_Model->SetRotation(m_Rotation);

	//���̃|�C���g���C�g��������
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

	//���̊O���̃|�C���g���C�g��������
	m_PointLightYellow = NewGO<PointLight>(0);
	m_PointLightYellow->SetPosition(LightPos);
	m_PointLightYellow->SetColor(Light2Color);
	m_PointLightYellow->SetRenge({ m_LightPower,attn,0.0f,0.0f });

	//�G�t�F�N�g��������
	m_Effect = NewGO<Effect>(0);
	m_Effect->Play(L"Assets/effect/Fire.efk");
	m_Effect->SetScale(EffectScale);
	m_Effect->SetPosition(LightPos);
	return true;
}

void Candle::Update()
{
	//���ɋ��������
	if (m_LightPower > MaxLightPower || m_LightPower < MinLightPower) {
		a *= -1.0f;
	}
	m_LightPower += a;
	m_PointLightRed->SetRenge({ m_LightPower,attn,0.0f,0.0f });
	m_Effect->SetScale(EffectScale*(m_LightPower / MaxLightPower));
}

void Candle::OnDestroy()
{
	//NewGO���������
	DeleteGO(m_Model);
	DeleteGO(m_PointLightRed);
	DeleteGO(m_PointLightYellow);
	DeleteGO(m_Effect);
}
