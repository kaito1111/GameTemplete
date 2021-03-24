#pragma once
class Arrow : public IGameObject
{
public:
	~Arrow()
	{
	}
	
	void Init(CVector3 pos, CQuaternion rot);
	void Update()override;
	
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Position = CVector3::Zero();
	CQuaternion m_Rotation = CQuaternion::Identity();
	CVector3 m_Forward = CVector3::Front();
	Animation m_Animation;
	AnimationClip m_AnimationClip[1];
};