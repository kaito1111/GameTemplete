#pragma once
#include "GameObject/IGameObject.h"
class LightBace : public ksEngine::IGameObject
{
public:
	LightBace() {};
	~LightBace() {};

	bool Start()override final;
	void OnDestroy()override final;	 
};