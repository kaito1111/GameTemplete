#include "pch.h"
#include "Character.h"

namespace {
	const float hpSpriteSizeY = 10.0f;	//スプライトの縦幅
	const float HpPosUp = 40.0f;		//HPをちょっと上に置く
	const float missingCoolTime = 1.0f; //m_HpTopTranslucentSpriteが減少するまでの時間
}
void Character::Destroy()
{
	//動的に確保したものたちを削除
	DeleteGO(m_Model);
	DeleteGO(m_HpUnderSprite);
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HpTopTranslucentSprite);
}
void Character::CharacterInit(wchar_t * filePath,const float radius, const float hight, const CVector3 & pos)
{
	//モデルを動的確保
	m_Model = NewGO<SkinModelRender>(0);
	//モデルをfilePathで呼び出す
	m_Model->Init(filePath);
	//キャラクターのモデルにセルフシャドウを落とさないように設定
	m_Model->SetShadowRecive(false);
	//キャラクターを作成
	m_CharaCon.Init(radius, hight, pos);
	//高さを記録
	m_Hight = hight;
}

void Character::Move(CVector3& move)
{
	Rotate();
	//重力を加算
	move.y -= 10.0f;
	//当たり判定を実行
	m_ModelPos = m_CharaCon.Execute(1.0f, move);
	//モデルの位置を設定
	m_Model->SetPosition(m_ModelPos);
	//モデルの回転を設定
	m_Model->SetRotation(m_ModelRot);
}

void Character::CharacterModelUpdate()
{
	//モデルの位置を設定
	m_Model->SetPosition(m_ModelPos);
	//モデルの回転率を設定
	m_Model->SetRotation(m_ModelRot);
	//モデルの大きさを設定
	m_Model->SetScale(m_ModelScale);
	//シャドウマップにモデルを登録
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_Model->GetModel());
}

void Character::ForwardUpdate()
{
	CMatrix mRot = CMatrix::Identity();
	//モデル行列を現在のモデルの回転で初期化
	mRot.MakeRotationFromQuaternion(m_ModelRot);
	//モデルの前方向を取得
	m_forward = { mRot.m[2][0],mRot.m[2][1],mRot.m[2][2] };
	//モデルをの前方向を正規化する
	m_forward.Normalize();
}

void Character::Heal()
{
	m_Hp = m_TranslucentScale * m_MaxHp;
}

void Character::SpriteInit(SpriteRender*& SpriteP, wchar_t* fileName, bool Is3dDraw,float HpX,float HpY)
{
	//HpをNew
	SpriteP = NewGO<SpriteRender>(3);
	//Hpをロード、画像の大きさも設定
	SpriteP->Init(fileName, HpX, HpY, Is3dDraw);
	m_spriteFix = -HpX / 2;
	//位置を更新
	SpriteP->SetPosition(m_HpPosition);
	if (Is3dDraw) {
		//基点を更新
		SpriteP->SetPivot({ SpriteRender::Left(),0.5f });
	}
	else {
		//基点を更新
		SpriteP->SetPivot({ SpriteRender::Right(),0.5f });
	}
	//カメラ方向に画像を向ける
	SpriteP->SetIsFaceCamera(true);
}
void Character::InitHpSprite(const float maxHp, const float hp, bool Is3dDraw, float HpX, float HpY)
{
	//HPの最大量を記録
	m_MaxHp = maxHp;
	//Hpを記録
	m_Hp = hp;
	SpriteInit(m_HpUnderSprite, L"HP_Under_Brack.dds", Is3dDraw, HpX, HpY);
	SpriteInit(m_HpTopSprite, L"HP_Top_Red.dds", Is3dDraw, HpX, HpY);
	SpriteInit(m_HpTopTranslucentSprite, L"HP_Top_Red.dds", Is3dDraw, HpX, HpY);
	m_HpTopTranslucentSprite->SetAlpha(0.5f);
	float SizeX = m_Hp / m_MaxHp;
	m_TranslucentScale = SizeX;
	m_HpTopTranslucentSprite->SetScale({ SizeX,1.0f,1.0f });
	//減少していく初期時間を設定
	m_HoldTimer = missingCoolTime;
}
void Character::SpriteUpdate()
{
	//Hpの位置を敵の位置に合わせる
	m_HpPosition = m_ModelPos;
	if (m_HpTopSprite->Get3DDraw()) {
		HpPosAdjustment();
	}
	//Hpの大きさをhpの残量に合わせる
	float SizeX = m_Hp / m_MaxHp;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	//Topの大きさを設定
	m_HpTopSprite->SetScale(SpriteSize);
	//Underの位置を設定
	m_HpUnderSprite->SetPosition(m_HpPosition);
	//Topの位置を設定
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
	//半透明hpのスケールと位置を更新
	m_HpTopTranslucentSprite->SetScale(translucentScale);
	m_HpTopTranslucentSprite->SetPosition(m_HpPosition);
}

void Character::HpPosAdjustment()
{
	m_HpPosition.y += m_Hight + HpPosUp;
	CVector3 AddSpritePos = g_camera3D.GetRight() * m_spriteFix;
	m_HpPosition -= AddSpritePos;
}