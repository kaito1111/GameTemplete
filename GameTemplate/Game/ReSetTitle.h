#pragma once
class Fade;
class ReSetTitle : public IGameObject
{
public:
	ReSetTitle(){}
	~ReSetTitle(){}

	bool Start()override final;
	void Update()override final;

	void SetFade(Fade*& fade) {
		m_fade = fade;
	}
private:
	Fade* m_fade = nullptr;
};

