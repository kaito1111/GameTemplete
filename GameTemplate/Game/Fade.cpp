#include "pch.h"
#include "Fade.h"
#include "Enemy/Enemy.h"
#include "Archer/Archer.h"
#include "Boss/Boss.h"
#include "Player/Player.h"

bool Fade::Start()
{
	m_FadeSprite = NewGO<SpriteRender>(5);
	m_FadeSprite->Init(L"Brack.dds");
	m_FadeSprite->SetAlpha(m_Alpha);
	m_LodingSprite = NewGO<SpriteRender>(6);
	m_LodingSprite->Init(L"Loading.dds", 250.0f, 250.0f);
	m_LodingSprite->SetPosition(m_LodingSpritePos);
	return true;
}

void Fade::Update()
{
	const float MaxStayCount = 0.5f;
	//����StayCount��MaxStayCount�𒴂��Ă��Ȃ����
	if (m_StayCount >= MaxStayCount) {
		QueryGOs<Enemy>("enemy", [&](Enemy* en)->bool {
			en->SetUpdateFlag(true);
			return true;
		});
		QueryGOs<Archer>("archer", [&](Archer* ac)->bool {
			ac->SetUpdateFlag(true);
			return true;
		});
		Boss* boss = FindGO<Boss>("boss", false);
		if (boss != nullptr) {
			boss->SetUpdateFlag(true);
		}
		Player* pl = FindGO<Player>("player", false);
		if (pl != nullptr) {
			pl->SetUpdateFlag(true);
		}
		//�����x��������
		const float alhpaSub = 0.2f;
		m_Alpha -= alhpaSub;
	}
	else {
		//�����Ă���Ώグ��
		const float alphaAdd = 0.2f;
		m_Alpha += alphaAdd;
	}
	//�����s�����Ȃ�StayCount���グ��
	if (m_Alpha > 1.1f) {
		QueryGOs<Enemy>("enemy", [&](Enemy* en)->bool {
			en->SetUpdateFlag(false);
			return true;
		});
		QueryGOs<Archer>("archer", [&](Archer* ac)->bool {
			ac->SetUpdateFlag(false);
			return true;
		});
		Boss* boss = FindGO<Boss>("boss", false);
		if (boss != nullptr) {
			boss->SetUpdateFlag(false);
		}
		Player* pl = FindGO<Player>("player",false);
		if (pl != nullptr) {
			pl->SetUpdateFlag(false);
		}
		m_StayCount += gameTime().GetFrameDeltaTime();
		m_Alpha = 1.1f;
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
