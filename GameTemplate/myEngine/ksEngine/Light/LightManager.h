#pragma once
#include "PointLight.h"
#include <list>
#include "light.h"
class LightBace;
class PointLight;

class LightManager 
{
	LightManager() {};
	~LightManager()
	{

	};
public:

	static LightManager* GetInstance() {
		static LightManager instance;
		return &instance;
	}

	void SetPointLight(PointLight* Point) {
		PointLights.push_back(Point);
	}

	//シングルトンなのでインスタンス化できないため
	//mainで明示的に呼んでいる
	void Start();
	void Update();

	void AddLight(LightBace* Light);
	void RemoveLight(LightBace* Light);
private:
	static const int MAX_POINT_LIGHT = 1024;
	SPointLight m_rawPointLight[MAX_POINT_LIGHT];
	std::list<PointLight*> PointLights;
	ID3D11Buffer* m_PointLightBuffer = nullptr;
	ID3D11Buffer* m_NumPointLightBuffer = nullptr;
};