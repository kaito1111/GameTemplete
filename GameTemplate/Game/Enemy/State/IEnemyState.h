#pragma once
class Enemy;
class IEnemyState
{
public:
	IEnemyState(Enemy* en) :
		m_enemy(en) 
	{
	};
	~IEnemyState() {};
	virtual void Update() = 0;
private:
	

	virtual bool IsPossibleMove() const {
		return true;
	}

	virtual bool IsPossibleRotate()const {
		return true;
	}
protected:
	Enemy* m_enemy = nullptr;
};

