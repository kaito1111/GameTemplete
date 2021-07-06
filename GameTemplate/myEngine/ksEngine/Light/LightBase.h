#pragma once

class LightBace : public ksEngine::IGameObject
{
public:
	LightBace() {};
	~LightBace() {};

	bool Start()override final;
	void OnDestroy()override final;	 
};