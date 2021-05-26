#include "pch.h"
#include "Character.h"

namespace {
	const float hpSpriteSizeY = 10.0f;	//�X�v���C�g�̏c��
	//HP��������Ə�ɒu��
	const float HpPosUp = 40.0f;
}
Character::~Character() {
	DeleteGO(m_Model);
	DeleteGO(m_HpUnderSprite);
	DeleteGO(m_HpTopSprite); 

}
void Character::CharacterInit(wchar_t * filePath, float radius, float hight, const CVector3 & pos)
{
	m_Model = NewGO<SkinModelRender>(0);
	m_Model->Init(filePath);
	m_CharaCon.Init(radius, hight, pos);
	m_Hight = hight;
}

void Character::Move(CVector3& move)
{
	Rotate();
	//�d�͂����Z
	move.y -= 10.0f;
	//�����蔻������s
	m_ModelPos = m_CharaCon.Execute(gameTime().GetFrameDeltaTime()*60.0f, move);
	//���f���̈ʒu��ݒ�
	m_Model->SetPosition(m_ModelPos);
	//���f���̉�]��ݒ�
	m_Model->SetRotation(m_ModelRot);
}

void Character::CharacterModelUpdate()
{
	m_Model->SetPosition(m_ModelPos);
	m_Model->SetRotation(m_ModelRot);
	m_Model->SetScale(m_ModelScale);
}

void Character::ForwardUpdate()
{
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationFromQuaternion(m_ModelRot);
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	m_forward.Normalize();
}

void Character::SpriteInit(SpriteRender*& SpriteP, wchar_t* fileName)
{
	//Hp��New
	SpriteP = NewGO<SpriteRender>(1);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	SpriteP->Init(fileName, m_HpScaleList[m_HpScale], hpSpriteSizeY, true);
	m_spriteFix = -m_HpScaleList[m_HpScale] / 2;
	//�ʒu���X�V
	SpriteP->SetPosition(m_HpPosition);
	//��_���X�V
	SpriteP->SetPivot({ SpriteRender::Left(),0.5f });
	//�J���������ɉ摜��������
	SpriteP->SetIsFaceCamera(true);
}
void Character::InitHpSprite(const float hp, HpScale hpScale)
{
	m_HpScale = hpScale;
	m_MaxHp = hp;
	m_Hp = hp;
	SpriteInit(m_HpUnderSprite, L"HP_Under_Brack.dds");
	SpriteInit(m_HpTopSprite, L"HP_Top_Red.dds");
}
void Character::SpriteUpdate()
{
	//Hp�̈ʒu��G�̈ʒu�ɍ��킹��
	m_HpPosition = m_ModelPos;
	HpPosAdjustment();
	//Hp�̑傫����hp�̎c�ʂɍ��킹��
	float SizeX = m_Hp / m_MaxHp;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	//Top�̑傫����ݒ�
	m_HpTopSprite->SetScale(SpriteSize);
	//Top�̈ʒu��ݒ�
	m_HpTopSprite->SetPosition(m_HpPosition);
	//Under�̈ʒu��ݒ�
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

void Character::HpPosAdjustment()
{
	m_HpPosition.y += m_Hight + HpPosUp;
	CVector3 AddSpritePos = g_camera3D.GetRight() * m_spriteFix;
	m_HpPosition -= AddSpritePos;
}