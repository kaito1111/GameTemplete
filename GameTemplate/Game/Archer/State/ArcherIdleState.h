#pragma once
#include "Archer/Archer.h"
class ArcherIdleState : public IArcherState
{
public:
	ArcherIdleState(Archer* a) :
		IArcherState(a){}
	~ArcherIdleState(){}
	void Update()override;
};

