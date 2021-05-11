#pragma once
#include "Archer/State/IArcherState.h"
class Archer;
class ArcherDethState :
	public IArcherState
{
public :
	ArcherDethState(Archer* ac) :
		IArcherState(ac) {

	}
	~ArcherDethState() {}

	void Update() {};
	bool IsPossibleHpDown() {
		return false;
	}
};

