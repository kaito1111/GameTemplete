#pragma once
class Archer;

class IArcherState
{
public:
	IArcherState(Archer* a):
	m_Archer(a){};
	virtual ~IArcherState() {};
	virtual void Start();
	virtual void Update();
protected:
	Archer* m_Archer = nullptr;
};

