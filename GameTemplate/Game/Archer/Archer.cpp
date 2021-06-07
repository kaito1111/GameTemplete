#include "pch.h"
#include "Archer.h"
#include "State/ArcherIdleState.h"
#include "State/ArcherAttackState.h"
#include "Archer/Arrow.h"
#include "State/ArcherDethState.h"

namespace {
	//攻撃できる判定に入った
	const float InPlayer = 500.0f;
	//視野角
	const float ViewAngle = 0.7f;

	const float MaxHp = 62.5f;			//Hp
	const float m_height = 150.0f;  //身長
	const float DethAlpha = 0.0f;
}

void Archer::OnDestroy()
{
	if (m_ActiveState != nullptr) {
		m_ActiveState = nullptr;
	}
	if (m_ArrowList.size() > 0) {
		auto list = m_ArrowList;
		for (auto i : list) {
			DeleteGO(i);
		}
	}
}

void Archer::HitDamage(const float damege) {
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
	m_player = FindGO<Player>("player");

	//絵を初期化
	InitHpSprite(MaxHp,HpScale::EnemyHP);

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
	CVector3 NextForward = m_player->GetPosition() - m_ModelPos;
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
	SpriteUpdate();
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
	CVector3 Diff = m_player->GetPosition() - m_ModelPos;
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
		m_HpUnderSprite->SetAlpha(DethAlpha);
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