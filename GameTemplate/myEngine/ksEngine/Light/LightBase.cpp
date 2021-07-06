#include "stdafx.h"
#include "LightBase.h"
#include "LightManager.h"
bool LightBace::Start()
{
	LightManager::GetInstance()->AddLight(this);
	return true;
}

void LightBace::OnDestroy()
{
	LightManager::GetInstance()->RemoveLight(this);
}
