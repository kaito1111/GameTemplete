#pragma once
#include "physics/PhysicsStaticObject.h"
/// <summary>
/// �X�e�[�W�̐ÓI�����I�u�W�F�N�g�����
/// </summary>
class PhysicsStageObject final : public IGameObject
{
public:

	/// <summary>
	/// �C���X�^���X�����������ƁA��x�����Ă΂��J�n����
	/// </summary>
	/// <remarks>
	/// Unity��Start()�֐��̎d�l�ɏ����B
	/// </remarks>
	/// <returns>
	/// true���A���Ă�����A�����������B
	/// �����t���[���ɂ킽���ď��������������ꍇ�́A
	/// �����������܂�false��Ԃ��B
	/// </returns>
	bool Start() override final;
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
	void OnDestroy()override final;
	/// <summary>
	/// ���f���̈ʒu��ݒ�
	/// ���̊֐��ł����ݒ肵�Ă��Ȃ�
	/// </summary>
	/// <param name="Pos">���f���̈ʒu</param>
	void SetPosition(const CVector3& Pos) {
		m_Pos = Pos;
	}

	/// <summary>
	/// ���f���̉�]�ʂ�ݒ�
	/// ���̊֐��ł����ݒ肵�Ă��Ȃ�
	/// </summary>
	/// <param name="Rot"></param>
	void SetRotation(CQuaternion Rot) {
		m_Rot = Rot;
	}

	/// <summary>
	/// ���f���̃t�@�C���p�X��ݒ�
	/// ���̊֐��ł����ݒ肵�Ă��Ȃ�
	/// </summary>
	/// <param name="name">�t�@�C���p�X</param>
	void SetObjectName(const wchar_t* name) {
		wcscpy(m_ObjectName,name);
	}
private:
	SkinModelRender* m_Model = nullptr;				//�ÓI�����I�u�W�F�N�g�̃��f��
	CVector3 m_Pos = CVector3::Zero();				//���f���̈ʒu
	CQuaternion m_Rot = CQuaternion::Identity();	//���f���̉�]��
	PhysicsStaticObject m_Pysics;					//�ÓI�����I�u�W�F�N�g
	wchar_t m_ObjectName[256] = {};					//���f���̃t�@�C���p�X
};

