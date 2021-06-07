#pragma once
#include "GameSceneFunction/Anime.h"
class PlayerAttack final : public IGameObject
{
public:
	PlayerAttack();
	~PlayerAttack();

	void Init(float atack, float aria,const CVector3& pos) {
		m_Attack = atack;
		m_Aria = aria;
		m_AttackPos = pos;
	}

	bool Start();
	void Update();
	void OnDestroy()override;
private:
	CVector3 m_AttackPos = CVector3::Zero();
	float m_Attack = 0.0f;
	float m_Aria = 0.0f;
	bool m_Hit = false;//UŒ‚‚ª‚P‰ñƒqƒbƒg‚µ‚½
	SkinModelRender* m_AttackModel = nullptr;
	SoundSource m_DamageSound;
};