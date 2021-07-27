#pragma once
#include "Player/weapon/IWeapon.h"
class Sword :
	public IWeapon
{
public :
	Sword() {};
	~Sword() {};

	void Start()override final;
	void Update()override final;
	void Delete()override final;

};

