#pragma once
#include "IBossState.h"
class BossNormalRoar:public IBossState
{
public:
	BossNormalRoar(Boss* boss) :
		IBossState(boss) {
		m_Effect = NewGO<Effect>(0);
		m_Effect->Play(L"Assets/effect/BossRoar.efk");
	};

	void Update()override;

private:
	Effect* m_Effect = nullptr;
};

