#include "pch.h"
#include "Archer.h"
#include "State/ArcherIdleState.h"
#include "State/ArcherAttackState.h"
#include "Archer/Arrow.h"
#include "State/ArcherDethState.h"

namespace {
	//スプライトの縦の大きさ
	const float SpriteHight = 10.0f;
	//HPをちょっと上に置く
	const float HpPosUp = 30.0f;
	//攻撃できる判定に入った
	const float InPlayer = 500.0f;
	//視野角
	const float ViewAngle = 0.7f;
	//スプライトの基点をずらしているので
	//そのズレを修正
	const float spriteFix = -50.0f;
}

void Archer::OnDestroy()
{
	if (m_ActiveState != nullptr) {
		m_ActiveState = nullptr;
	}
	DeleteGO(m_HpTopSprite);
	DeleteGO(m_HpUnderSprite);
	if (m_ArrowList.size() > 0) {
		auto list = m_ArrowList;
		for (auto i : list) {
			DeleteGO(i);
		}
	}
}

void Archer::HitDamege(const float damege) {
	//死んでないならHpを減らす
	if (m_ActiveState->IsPossibleHpDown()) {
		m_Hp -= damege;
	}
	//Hpが0以上ならダメージモーションを
	if (m_Hp > 0) {
		m_NextState = State::Damage;
	}
	//以下ならhpを0にして殺す
	else {
		m_Hp = 0;
		m_NextState = State::Deth;
	}
}

bool Archer::Start()
{
	//スポーン位置を設定
	m_ModelPos = m_SpownPositon;

	//モデルを初期化
	CharacterInit(L"Archer.cmo", 35.0f, 135.0f,m_ModelPos);

	//アニメーションを初期化
	InitAnimetion();

	//現在の状態を待機状態へ
	m_ActiveState = new ArcherIdleState(this);

	//プレイヤーを見つける
	m_Player = FindGO<Player>("player");

	//絵を初期化
	InitSprite();
	return true;
}

void Archer::InitModel()
{
	//モデルをnew
	m_Model = NewGO<SkinModelRender>(0);
	//モデルをロード
	m_Model->Init(L"Archer.cmo");
	//モデルの位置を設定
	m_Model->SetPosition(m_ModelPos);
	//モデルの回転量を設定
	m_Model->SetRotation(m_ModelRot);
}

void Archer::InitAnimetion()
{
	//各アニメーションイベントをロード
	LoadAnimation(m_AnimationClip[State::Idle], L"ArcherIdle.tka");
	m_AnimationClip[State::Idle].SetLoopFlag(true);
	LoadAnimation(m_AnimationClip[State::Attack], L"ArcherAttack.tka");
	LoadAnimation(m_AnimationClip[State::Damage], L"ArcherDamage.tka");
	LoadAnimation(m_AnimationClip[State::Deth], L"ArcherDeth.tka");

	//アニメーションを登録
	InitAnimation(m_AnimationClip,State::Num);
	//イベントリスナーを登録
	m_Animation.AddAnimationEventListener([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimEvent(eventName);
	});
}

void Archer::InitSprite()
{
	//上のHpバーを初期化
	InitHpTop();
	//下のHpバーを初期化
	InitHpUnder();
}

void Archer::InitHpTop()
{
	//hpをnew
	m_HpTopSprite = NewGO<SpriteRender>(2);
	//Hpをロード、画像の大きさも設定
	m_HpTopSprite->Init(L"HP_Top_Red.dds", m_Hp, SpriteHight, true);
	//位置を更新
	m_HpTopSprite->SetPosition(m_HpPosition);
	//大きさを更新
	//Hpの大きさをhpの残量に合わせる
	float SizeX = m_Hp * m_SpriteSize;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	m_HpTopSprite->SetScale(SpriteSize);
	//基点を更新
	m_HpTopSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//カメラ方向に画像を向ける
	m_HpTopSprite->SetIsFaceCamera(true);
}

void Archer::InitHpUnder()
{
	//HpをNew
	m_HpUnderSprite = NewGO<SpriteRender>(1);
	//Hpをロード、画像の大きさも設定
	m_HpUnderSprite->Init(L"HP_Under_Brack.dds", m_Hp, SpriteHight, true);
	//位置を更新
	m_HpUnderSprite->SetPosition(m_HpPosition);
	//大きさを更新
	//Hpの大きさをhpの残量に合わせる
	float SizeX = m_Hp * m_SpriteSize;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	m_HpUnderSprite->SetScale(SpriteSize);
	//基点を更新
	m_HpUnderSprite->SetPivot({ SpriteRender::Left(),SpriteRender::Up() });
	//カメラ方向に画像を向ける
	m_HpUnderSprite->SetIsFaceCamera(true);
}

void Archer::OnAnimEvent(const wchar_t * eventName)
{
	if (wcscmp(eventName, L"SpownArrow") == 0) {
		//矢を作る
		Arrow* m_Arrow = NewGO<Arrow>(0,"arrow");
		//矢の初期化
		m_Arrow->Init(this);
		m_ArrowList.push_back(m_Arrow);
		m_HasArrow = m_Arrow;
	}
	if (wcscmp(eventName, L"bindArrow") == 0) {
		m_isAttachArrow = true;
	}
	if (wcscmp(eventName, L"ShotArrow") == 0) {
		m_ArrowList.back()->SetShot();
		m_HasArrow = nullptr;
	}
	if(wcscmp(eventName, L"PlayerFacingFinish") == 0) {
		m_IsPlayerFacing = false;
	}
}

void Archer::Rotate()
{
	CVector3 NextForward = m_Player->GetPosition() - m_ModelPos;
	float rotAngle = atan2(NextForward.x, NextForward.z);
	m_ModelRot.SetRotation(CVector3::AxisY(), rotAngle);
}


void Archer::CalcArrowPosAndRotationFromAttachBone(CVector3& pos, CQuaternion& rot, const wchar_t* AttchName, const wchar_t* TargetName)
{
	//二つのアタッチボーンを取得。
	Bone* attachBone = m_Model->GetModel().FindBone(AttchName);
	Bone* attachBone2 = m_Model->GetModel().FindBone(TargetName);
	//骨から座標、回転、拡大率を取得する。
	CVector3 posTmp;
	CQuaternion rotTmp;
	CVector3 scaleTmp;
	//arrow_attachは矢の位置を決めるための骨。
	attachBone->CalcWorldTRS(pos, rotTmp, scaleTmp);
	//arrow_attach_2は矢の向きを決めるための骨。
	attachBone2->CalcWorldTRS(posTmp, rotTmp, scaleTmp);

	//矢の向きを計算する。
	CVector3 dir = posTmp - pos;
	dir.Normalize();
	//矢の回転クォータニオンを計算する。
	rot.SetRotation(CVector3::AxisZ(), dir);
}

void Archer::Update()
{
	//アニメーションを更新
	AnimationUpdate();
	//絵を更新
	UpdateSprite();
	//現在の状態の更新を呼ぶ
	m_ActiveState->Update();
	//状態を更新
	UpdateState(m_NextState);
	//前方向の更新
	ForwardUpdate();
	//モデルの更新
	CharacterModelUpdate();
}

void Archer::AnimationUpdate()
{
	//現在のアニメーションを再生させる
	m_Animation.Play(m_State, 0.2f);
	//アニメーションを再生
	m_Animation.Update(gameTime().GetFrameDeltaTime());
}

bool Archer::IsAttack()
{
	if (GetAsyncKeyState('U')) {
		return true;
	}//距離の差を測る
	CVector3 Diff = m_Player->GetPosition() - m_ModelPos;
	//もしプレイヤーが範囲内にいるなら
	if (Diff.Length() < InPlayer) {
		Diff.Normalize();
		//プレイヤーの方向を取り
		float Dir = m_forward.Dot(Diff);
		//視野に入れば
		if (Dir > ViewAngle) {
			//攻撃できる
			return true;
		}
	}
	return false;
}



void Archer::UpdateState(int st)
{
	switch (st)
	{
	case State::Idle:
		m_ActiveState = new ArcherIdleState(this);
		break;
	case State::Attack:
		m_ActiveState = new ArcherAttackState(this);
		break;
	case State::Deth:
		m_ActiveState = new ArcherDethState(this);
		m_CharaCon.RemoveRigidBoby();
		DeleteGO(m_HasArrow);
		m_HasArrow = nullptr;
		break;
	case State::Damage:
		DeleteGO(m_HasArrow);
		m_HasArrow = nullptr;
		break;
	case State::Num:
		break;
	default:
		break;
	}
	m_State = st;
}

void Archer::UpdateSprite()
{
	//Hpの位置を敵の位置に合わせる
	m_HpPosition = m_ModelPos;
	HpPosAdjustment();
	//Hpの大きさをhpの残量に合わせる
	float SizeX = m_Hp * m_SpriteSize;
	CVector3 SpriteSize = CVector3::One();
	SpriteSize.x = SizeX;
	//大きさを設定
	m_HpTopSprite->SetScale(SpriteSize);
	//Topの位置を設定
	m_HpTopSprite->SetPosition(m_HpPosition);
	//Underの位置を設定
	m_HpUnderSprite->SetPosition(m_HpPosition);
}

void Archer::HpPosAdjustment()
{
	m_HpPosition.y += m_height + HpPosUp;
	CVector3 AddSpritePos = g_camera3D.GetRight() * spriteFix;
	m_HpPosition -= AddSpritePos;
}