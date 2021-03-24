#pragma once
#include "IArcherState.h"
class Archer;
class ArcherAttackState : public IArcherState
{
public:
	ArcherAttackState(Archer* a) :
		IArcherState(a) {};
	~ArcherAttackState() {};

	void Update()override;
};

