#pragma once
class Player2 final :public IGameObject
{
public:
	Player2();
	~Player2();
	bool Start();
	void Update();
	void Draw();
private:
	SkinModel m_skin;
	CVector3 m_pos= CVector3::Zero();
};

