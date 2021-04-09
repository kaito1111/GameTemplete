#pragma once
class Boss : public IGameObject
{
	enum State {
		Walk,
		Attack,
		JumpAttack,
		Scream,
		StateNum,
	};
public:
	~Boss() {};

	bool Start()override;
	void Update()override;

	void SetPosition(const CVector3& pos) {
		m_Pos = pos;
	}

	void SetRotation(const CQuaternion& rot) {
		m_Rot = rot;
	}
private:
	SkinModelRender* m_Model = nullptr;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	
	Animation m_Animation;
	AnimationClip m_AnimationClip[StateNum];
};

