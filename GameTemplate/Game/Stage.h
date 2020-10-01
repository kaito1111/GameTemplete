#pragma once
class Stage :public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void Draw();

private:
	SkinModel m_Model;
	CVector3 m_pos = CVector3::Zero();

};

