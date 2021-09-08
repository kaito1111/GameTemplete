#pragma once
#include "character/characterController.h"
class Character :public IGameObject
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Character() {};
	/// <summary>
	/// ���̃N���X�͌p�����Ƃ��Ďg����̂�Ondestroy���g���Ȃ��̂�
	/// �C�ӂ̃^�C�~���O�ł��̊֐����Ăт��̃N���X�œ��I�m�ۂ������̂��폜����
	/// �G���[�͓f���܂���2��ȏ�Ă΂Ȃ��悤�ɋC��t���܂��傤(���ʂȂ̂�)
	/// </summary>
	void Destroy();

	/// <summary>
	/// ���f���̏�����
	/// </summary>
	/// <param name="filePath">���f���̃t�@�C���p�X</param>
	/// <param name="radius">CharacterController�ɓo�^���������a</param>
	/// <param name="hight">CharacterController�ɓo�^����������</param>
	/// <param name="pos">CharacterController�ɓo�^�����������ʒu</param>
	void CharacterInit(wchar_t* filePath,const float radius,const float hight, const CVector3& pos);

	/// <summary>
	/// ���f���̉�]�������e���ݒ�
	/// </summary>
	virtual void Rotate() = 0;

	/// <summary>
	/// ���f���̉�]�ʂ�ݒ�
	/// </summary>
	/// <param name="rot">��]��</param>
	void SetRotation(const CQuaternion& rot) {
		m_ModelRot = rot;
	}

	/// <summary>
	/// ���f���̈ʒu���擾
	/// </summary>
	/// <returns>���f���̈ʒu</returns>
	const CVector3& GetPosition() const {
		return m_ModelPos;
	}

	/// <summary>
	/// ���x���Ŏ擾�����ʒu�Ƀ��f����z�u����֐�
	/// �������ɂ����Ă΂�Ȃ��̂�Spowner�N���X�ł����Ă΂�Ȃ��A�A�A�͂��A�A
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	void SetSporwnModelPosition(const CVector3& pos) {
		m_ModelPos = pos;
	}
	/// <summary>
	/// CharacterController�𓮂���
	/// </summary>
	/// <param name="move">�ړ���</param>
	void Move(CVector3& move);

	/// <summary>
	/// ���f�����X�V����
	/// </summary>
	void CharacterModelUpdate();

	/// <summary>
	/// �O�������X�V����
	/// </summary>
	virtual void ForwardUpdate();

	/// <summary>
	/// ���f���̈ړ��ʂ��擾
	/// </summary>
	/// <returns>�ړ���</returns>
	const CVector3& GetMoveSpeed()const {
		return m_MoveSpeed;
	}

	/// <summary>
	/// ���f���̉�]�����擾
	/// </summary>
	/// <returns>��]��</returns>
	const CQuaternion& GetRot()const {
		return m_ModelRot;
	}
	
	/// <summary>
	/// hp�ƍő�Hp�����������Ă���
	/// </summary>
	/// <param name="maxHp">Hp�̍ő�</param>
	/// <param name="hp">HP</param>
	/// <param name="Is3dDraw">3D�`�悵�܂����H</param>
	/// <param name="HpX">�X�v���C�g�̉���</param>
	/// <param name="HpY">�X�v���C�g�̗���</param>
	void InitHpSprite(const float maxHp,const float hp, bool Is3dDraw = true,float HpX= 100.0f,float HpY= 10.0f);

	/// <summary>
	/// �X�v���C�g��hp�̎c��Ƃ����v�Z���Ă���
	/// </summary>
	void SpriteUpdate();

	/// <summary>
	/// �U���������������ɌĂ΂��
	/// �֐����ɃX�e�[�g��ύX���鏈��������̂ŏ������z�֐��ɂ���
	/// </summary>
	/// <param name="damege">�_���[�W��</param>
	virtual	void HitDamage(const float damege) = 0;

	/// <summary>
	/// �U�����󂯂����A�v���C���[�̍U����������΁A
	/// TranslucentSprite�̈ʒu�܂ŉ񕜂���
	/// �v���C���[�����g���Ă��Ȃ�
	/// </summary>
	void Heal();

	/// <summary>
	/// �����Ɏ����Ă����ʒu��Hp�X�v���C�g���ꗥ�Ɉړ�������֐�
	/// </summary>
	/// <param name="pos">Hp�X�v���C�g�̈ʒu</param>
	void SetHpPosition(CVector3 pos) {
		m_HpTopSprite->SetPosition(pos);
		m_HpTopTranslucentSprite->SetPosition(pos);
		m_HpUnderSprite->SetPosition(pos);
	}

	/// <summary>
	/// �c��Hp���擾
	/// </summary>
	/// <returns>�c��HP</returns>
	float GetHp()const {
		return m_Hp;
	}
private:
	/// <summary>
	/// Hp�X�v���C�g�̏�����
	/// </summary>
	/// <param name="SpriteP">���I�m�ۂ���X�v���C�g�̃|�C���^</param>
	/// <param name="fileName">Hp�X�v���C�g�Ɏg���摜</param>
	/// <param name="Is3dDraw">3D�`�悵�܂����H</param>
	/// <param name="HpX">�X�v���C�g�̉���</param>
	/// <param name="HpY">�X�v���C�g�̗���</param>
	void SpriteInit(SpriteRender*& SpriteP, wchar_t* fileName, bool Is3dDraw, float HpX, float HpY);

	/// <summary>
	/// Hp�X�v���C�g���Y���Ă���̂ŏC������֐�
	/// </summary>
	void HpPosAdjustment();
protected:
	SkinModelRender* m_Model = nullptr;					//���f��
	CVector3 m_ModelPos = CVector3::Zero();				//���f���̈ʒu
	CQuaternion m_ModelRot = CQuaternion::Identity();	//���f���̉�]
	CVector3 m_ModelScale = CVector3::One();			//���f���̑傫��
	CharacterController m_CharaCon;						//�L�����R��

	CVector3 m_MoveSpeed = CVector3::Zero();			//�ړ���
	CVector3 m_forward = CVector3::Front();				//�O����

	SpriteRender* m_HpTopSprite = nullptr;				//�c��Hp��\���X�v���C�g
	SpriteRender* m_HpUnderSprite = nullptr;			//�c��Hp�X�v���C�g�̉��ɂ���X�v���C�g
	
	CVector3 m_HpPosition = CVector3::Zero();			//Hp�X�v���C�g�̈ʒu
	float m_Hp = 0.0f;									//�c��Hp
	float m_MaxHp = 0.0f;								//�ő�Hp
	float m_Hight = 0.0f;								//����
	
	float m_spriteFix = -50.0f;							//�X�v���C�g�̊�_�����炵�Ă���̂ł��̃Y�����C��
														
	SpriteRender* m_HpTopTranslucentSprite = nullptr;   //Hp�����X�Ɍ������Ă����̂�\������X�v���C�g
	float m_TranslucentScale = 1.0f;					//m_HpTopTranslucentSprite�̓����x
	float m_HoldTimer = 0.0f;							//����܂łɑҋ@���鎞��
};

