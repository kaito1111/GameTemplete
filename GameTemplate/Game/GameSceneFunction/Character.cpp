#include "pch.h"
#include "Character.h"

namespace {
	const float hpSpriteSizeY = 10.0f;	//�X�v���C�g�̏c��
	const float HpPosUp = 40.0f;		//HP��������Ə�ɒu��
	const float missingCoolTime = 1.0f; //m_HpTopTranslucentSprite����������܂ł̎���
}
void Character::Destroy()
{
	//���I�Ɋm�ۂ������̂������폜
	DeleteGO(m_Model);
	DeleteGO(m_HpUnderSprite);
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HpTopTranslucentSprite);
}
void Character::CharacterInit(wchar_t * filePath,const float radius, const float hight, const CVector3 & pos)
{
	//���f���𓮓I�m��
	m_Model = NewGO<SkinModelRender>(0);
	//���f����filePath�ŌĂяo��
	m_Model->Init(filePath);
	//�L�����N�^�[�̃��f���ɃZ���t�V���h�E�𗎂Ƃ��Ȃ��悤�ɐݒ�
	m_Model->SetShadowRecive(false);
	//�L�����N�^�[���쐬
	m_CharaCon.Init(radius, hight, pos);
	//�������L�^
	m_Hight = hight;
}

void Character::Move(CVector3& move)
{
	Rotate();
	//�d�͂����Z
	move.y -= 10.0f;
	//�����蔻������s
	m_ModelPos = m_CharaCon.Execute(1.0f, move);
	//���f���̈ʒu��ݒ�
	m_Model->SetPosition(m_ModelPos);
	//���f���̉�]��ݒ�
	m_Model->SetRotation(m_ModelRot);
}

void Character::CharacterModelUpdate()
{
	//���f���̈ʒu��ݒ�
	m_Model->SetPosition(m_ModelPos);
	//���f���̉�]����ݒ�
	m_Model->SetRotation(m_ModelRot);
	//���f���̑傫����ݒ�
	m_Model->SetScale(m_ModelScale);
	//�V���h�E�}�b�v�Ƀ��f����o�^
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Model->GetModel());
}

void Character::ForwardUpdate()
{
	CMatrix mRot = CMatrix::Identity();
	//���f���s������݂̃��f���̉�]�ŏ�����
	mRot.MakeRotationFromQuaternion(m_ModelRot);
	//���f���̑O�������擾
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	//���f�����̑O�����𐳋K������
	m_forward.Normalize();
}

void Character::Heal()
{
	m_Hp = m_TranslucentScale * m_MaxHp;
}

void Character::SpriteInit(SpriteRender*& SpriteP, wchar_t* fileName, bool Is3dDraw,float HpX,float HpY)
{
	//Hp��New
	SpriteP = NewGO<SpriteRender>(3);
	//Hp�����[�h�A�摜�̑傫�����ݒ�
	SpriteP->Init(fileName, HpX, HpY, Is3dDraw);
	m_spriteFix = -HpX / 2;
	//�ʒu���X�V
	SpriteP->SetPosition(m_HpPosition);
	if (Is3dDraw) {
		//��_���X�V
		SpriteP->SetPivot({ SpriteRender::Left(),0.5f });
	}
	else {
		//��_���X�V
		SpriteP->SetPivot({ SpriteRender::Right(),0.5f });
	}
	//�J���������ɉ摜��������
	SpriteP->SetIsFaceCamera(true);
}
void Character::InitHpSprite(const float maxHp, const float hp, bool Is3dDraw, float HpX, float HpY)
{
	//HP�̍ő�ʂ��L�^
	m_MaxHp = maxHp;
	//Hp���L�^
	m_Hp = hp;
	SpriteInit(m_HpUnderSprite, L"HP_Under_Brack.dds", Is3dDraw, HpX, HpY);
	SpriteInit(m_HpTopSprite, L"HP_Top_Red.dds", Is3dDraw, HpX, HpY);
	SpriteInit(m_HpTopTranslucentSprite, L"HP_Top_Red.dds", Is3dDraw, HpX, HpY);
	m_HpTopTranslucentSprite->SetAlpha(0.5f);
	float SizeX = m_Hp / m_MaxHp;
	m_TranslucentScale = SizeX;
	m_HpTopTranslucentSprite->SetScale({ SizeX,1.0f,1.0f });
	//�������Ă����������Ԃ�ݒ�
	m_HoldTimer = missingCoolTime;
}
void Character::SpriteUpdate()
{
	//Hp�̈ʒu��G�̈ʒu�ɍ��킹��
	m_HpPosition = m_ModelPos;
	if (m_HpTopSprite->Get3DDraw()) {
		HpPosAdjustment();
	}
	//Hp�̑傫����hp�̎c�ʂɍ��킹��
	float SizeX = m_Hp / m_MaxHp;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	//Top�̑傫����ݒ�
	m_HpTopSprite->SetScale(SpriteSize);
	//Under�̈ʒu��ݒ�
	m_HpUnderSprite->SetPosition(m_HpPosition);
	//Top�̈ʒu��ݒ�
	m_HpTopSprite->SetPosition(m_HpPosition);
	float diff = fabsf(m_TranslucentScale - SpriteSize.x);
	if (diff > 0.01f) {
		m_HoldTimer -= gameTime().GetFrameDeltaTime();
	}
	if (m_HoldTimer < 0.0f) {
		m_TranslucentScale -= 0.005f;
	}
	if (diff <= 0.01f) {
		m_HoldTimer = missingCoolTime;
	}
	CVector3 translucentScale = SpriteSize;
	translucentScale.x = m_TranslucentScale;
	//������hp�̃X�P�[���ƈʒu���X�V
	m_HpTopTranslucentSprite->SetScale(translucentScale);
	m_HpTopTranslucentSprite->SetPosition(m_HpPosition);
}

void Character::HpPosAdjustment()
{
	m_HpPosition.y += m_Hight + HpPosUp;
	CVector3 AddSpritePos = g_camera3D.GetRight() * m_spriteFix;
	m_HpPosition -= AddSpritePos;
}