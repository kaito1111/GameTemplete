#pragma once
#include <Effekseer.h>
class Item:public IGameObject
{
public:
	Item();
	~Item();

	bool Start()override final;
	void Update()override final;

};

