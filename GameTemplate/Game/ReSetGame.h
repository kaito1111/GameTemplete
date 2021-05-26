#pragma once
class Fade;
class ReSetGame : public IGameObject
{
public:
	ReSetGame() {}
	~ReSetGame() {}

	bool Start()override;
	void Update()override;
	
	void SetFade(Fade* fa) {
		m_Fade = fa;
	}
private:
	Fade* m_Fade = nullptr;
};

