#pragma once
class Player;
/// <summary>
/// �U���̏������܂Ƃ߂��N���X
/// </summary>
class Attack : public IGameObject
{
public:
	/// <summary>
	/// �U���̏ڍׂ�ݒ肷�鏉�����֐�
	/// </summary>
	/// <param name="Damege"></param>
	/// <param name="Aria"></param>
	/// <param name="pos"></param>
	void Init(float Damege, float Aria, const CVector3& pos) {
		m_Area = Aria;
		m_Damege = Damege;
		m_Position = pos;
		m_Player = FindGO<Player>("player");
		m_DamageSound.Init(L"HitAttack.wav");
#ifdef _DEBUG
		m_AttackModel = NewGO<SkinModelRender>(0);
		m_AttackModel->Init(L"DebugShere.cmo");
		m_AttackModel->SetPosition(m_Position);
		CVector3 ModelScale = { m_Area,m_Area,1.0f };
		m_AttackModel->SetScale(ModelScale);
#endif
	}
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �C���X�^���X���j������鎞�ɌĂ΂��֐��B
	/// </summary>
	/// <remarks>
	/// �{�G���W���Ŏ������Ă���A�Q�[���I�u�W�F�N�g���폜����
	/// DeleteGO�֐��́A�����ɃC���X�^���X���폜����킯�ł͂Ȃ��A
	/// 1�t���[���x��ăC���X�^���X���폜�����B
	/// ���̂��߁A�f�X�g���N�^�̌Ăяo�����ADeleteGO�̌Ăяo������1�t���[���x��邱�ƂƂȂ�B
	/// DeleteGO���Ă΂ꂽ�^�C�~���O�ŁA�s�������I��������OnDestroy()�ɋL�q����B
	/// </remarks>
	void OnDestroy()override;
private:
	float m_Damege = 0.0f;						//�U����
	float m_Area = 0.0f;						//�U���͈�
	Player* m_Player = nullptr;					//�v���C���[�̃|�C���^
	CVector3 m_Position = CVector3::Zero();		//�U���ʒu
#ifdef _DEBUG
	SkinModelRender* m_AttackModel = nullptr;	//�U���͈͂�\�������f��
#endif
	SoundSource m_DamageSound;					//�U����
};

