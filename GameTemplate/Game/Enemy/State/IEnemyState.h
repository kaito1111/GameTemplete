#pragma once
class IEnemyState
{
public:
	IEnemyState(Enemy* en) :
		m_enemy(en) {};
	~IEnemyState() {};
private:
	
	virtual void Update() = 0;

	virtual bool IsPossibleMove() const {
		return true;
	}

	virtual bool IsPossibleRotate()const {
		return true;
	}
protected:
	Enemy* m_enemy = nullptr;
};

