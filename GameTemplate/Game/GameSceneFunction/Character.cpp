#include "pch.h"
#include "Character.h"

namespace {
	const float hpSpriteSizeY = 10.0f;	//スプライトの縦幅
	//HPをちょっと上に置く
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
	//重力を加算
	move.y -= 10.0f;
	//当たり判定を実行
	m_ModelPos = m_CharaCon.Execute(gameTime().GetFrameDeltaTime()*60.0f, move);
	//モデルの位置を設定
	m_Model->SetPosition(m_ModelPos);
	//モデルの回転を設定
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
	//HpをNew
	SpriteP = NewGO<SpriteRender>(1);
	//Hpをロード、画像の大きさも設定
	SpriteP->Init(fileName, m_HpScaleList[m_HpScale], hpSpriteSizeY, true);
	m_spriteFix = -m_HpScaleList[m_HpScale] / 2;
	//位置を更新
	SpriteP->SetPosition(m_HpPosition);
	//基点を更新
	SpriteP->SetPivot({ SpriteRender::Left(),0.5f });
	//カメラ方向に画像を向ける
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
	//Hpの位置を敵の位置に合わせる
	m_HpPosition = m_ModelPos;
	HpPosAdjustment();
	//Hpの大きさをhpの残量に合わせる
	float SizeX = m_Hp / m_MaxHp;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	//Topの大きさを設定
	m_HpTopSprite->SetScale(SpriteSize);
	//Topの位置を設定
	m_HpTopSprite->SetPosition(m_HpPosition);
	//Underの位置を設定
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

void Character::HpPosAdjustment()
{
	m_HpPosition.y += m_Hight + HpPosUp;
	CVector3 AddSpritePos = g_camera3D.GetRight() * m_spriteFix;
	m_HpPosition -= AddSpritePos;
}