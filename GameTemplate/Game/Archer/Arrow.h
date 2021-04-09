#pragma once
class Archer;
class ArcherAttack;
class Arrow : public IGameObject
{
public:
	//�f�X�g���N�^
	~Arrow()
	{
	}
	//������
	void Init(Archer* arc);
	//�X�V
	void Update()override;
	//������Ƃ��ɌĂ΂��
	void OnDestroy()override;
	//�|�Ƀo�C���h����Ƃ��ɃZ�b�g����
	void SetArrowBindFlag() {
		m_isBaindArrow = true;
	}
	void SetShot() {
		IsShot = true;
	}
private:
	SkinModelRender* m_Model = nullptr;	//���f��
	Archer* m_Archer = nullptr;			//����o���N���X
	bool m_isBaindArrow = false;
	CVector3 m_Pos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	bool IsShot = false;
	float m_ElapsedTime = 0.0f;
	ArcherAttack* m_ArcherAttack = nullptr;
};