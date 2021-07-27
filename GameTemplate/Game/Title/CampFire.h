#pragma once
class CampFire : public IGameObject
{
public:
	CampFire() {}
	~CampFire(){}

	bool Start()override final;
	void Update()override final;
	void OnDestroy()override final;

	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	float GetMinLightPow() {
		float minLightPow = 1000.0f;
		for (float lightPow : m_lightPowArray) {
			minLightPow = min(lightPow, minLightPow);
		}
		return minLightPow;
	}
	float GetLightPow()const {
		return m_LightPower;
	}
	float GetMaxLightPow() {
		float maxLightPow = 1.0f;
		for (float lightPow : m_lightPowArray) {
			maxLightPow = max(lightPow, maxLightPow);
		}
		return maxLightPow;
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Position = CVector3::Zero();
	PointLight* m_PointLight = nullptr;
	static const int m_lightPowArraySize = 15;
	const float m_lightPowArray[m_lightPowArraySize] = {
		270.0f,260.0f,220.0,300.0f,40.0f,
		300.0f,280.0f,250.0f,290.0f,240.0f,
		320.0f,260.0f,250.0f,260.0f,270.0f
	};
	int m_currentLigPowNum = 0;
	float m_LightPower = 10.0f;
	float m_LightPower2 = 250.0f;
	float a = -1.5f;
	float a2 = -1.5f;
	SoundSource m_Sound;
	float m_ScaleTime = 0.0f; 
	PointLight*	m_PointLight2 = nullptr;
	bool m_Big = false;
	Effect* m_effect = nullptr;
};

