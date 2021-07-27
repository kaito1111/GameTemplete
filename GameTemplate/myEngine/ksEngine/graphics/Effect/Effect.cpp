#include "stdafx.h"
#include "Effect.h"

void Effect::Release()
{
	if (m_handle != -1) {
		g_graphicsEngine->GetEffectEngine().Stop(m_handle);
	}
}

void Effect::Play(const wchar_t * filePath)
{
	int nameKey = Util::MakeHash(filePath);
	EffectEngine& ee = g_graphicsEngine->GetEffectEngine();
	m_effect = ee.GetResourceManager().GetResource(nameKey);
	if (m_effect == nullptr) {
		//���o�^
		m_effect = ee.CreateEffekseerEffect(filePath);
		if (m_effect == nullptr) {
			MessageBox(
				NULL,
				TEXT("FilePath�����������ł��B\nFilePath���ԈႦ�Ă��Ȃ����m�F���Ă�������"),
				TEXT("Effect"),
				MB_ICONWARNING
			);
			std::abort();
		}
		ee.GetResourceManager().RegistResource(nameKey, m_effect);
	}
	m_handle = g_graphicsEngine->GetEffectEngine().Play(m_effect);
}

bool Effect::IsPlay() const
{
	return g_graphicsEngine->GetEffectEngine().GetEffekseerManager().GetShown(m_handle);
}

void Effect::Update()
{
	CMatrix mTrans, mRot, mScale, mBase;
	mTrans.MakeTranslation(m_Position);
	mRot.MakeRotationFromQuaternion(m_Rotarion);
	mScale.MakeScaling(m_Scale);
	mBase = mScale * mRot;
	mBase = mBase * mTrans;
	g_graphicsEngine->GetEffectEngine().GetEffekseerManager().SetBaseMatrix(m_handle, mBase);
	if (IsPlay() == false) {
		//�Đ�����������I���
		DeleteGO(this);
	}
}
