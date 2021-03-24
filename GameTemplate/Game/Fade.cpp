#include "pch.h"
#include "Fade.h"

bool Fade::Start()
{
	m_FadeSprite = NewGO<SpriteRender>(0);
	m_FadeSprite->Init(L"Assets/sprite/Brack.dds");
	m_FadeSprite->SetAlpha(m_Alpha);
	m_LodingSprite = NewGO<SpriteRender>(0);
	m_LodingSprite->Init(L"Assets/sprite/Loading.dds", 250.0f, 250.0f);
	m_LodingSprite->SetPosition(m_LodingSpritePos);
	return true;
}

void Fade::Update()
{
	const int MaxStayCount = 150;
	//����StayCount��MaxStayCount�𒴂��Ă��Ȃ����
	if (m_StayCount <= MaxStayCount) {
		//�����x��������
		const float alhpaSub = 0.2f;
		m_Alpha -= alhpaSub;
	}
	else {
		//�����Ă���Ώグ��
		const float alphaAdd = 0.5f;
		m_Alpha += alphaAdd;
	}
	//���������Ȃ�StayCount���グ��
	if (m_Alpha > 1.0f) {
		m_StayCount++;
		m_Alpha = 1.0f;
	}
	const float OneFrameLodingAngle = 6.0f;
	m_Angle += OneFrameLodingAngle;
	CQuaternion LoadingRot;
	LoadingRot.SetRotationDeg(CVector3::AxisZ(), m_Angle);
	m_LodingSprite->SetRotation(LoadingRot);
	m_LodingSprite->SetAlpha(m_Alpha);
	m_FadeSprite->SetAlpha(m_Alpha);
	//�A���t�@�l���}�C�i�X�Ȃ̂Ŗ�ڂ��I��
	if (m_Alpha < 0.0f) {
		DeleteGO(this);
	}
	//�t�F�[�h���̓Q�[���J�����������\�������邩��
	//�������ł��A�b�v�f�[�g������
	g_camera3D.Update();
}

void Fade::OnDestroy()
{
	DeleteGO(m_FadeSprite);
	DeleteGO(m_LodingSprite);
}
