#pragma once
class Player;
#include "character/CharacterController.h"
#include "graphics/SpringCamera.h"

/// <summary>
/// �v���C���[��ǂ�������J�����N���X
/// </summary>
class GameCamera :public IGameObject
{
public:
	/// <summary>
	/// �J�����̏��������̉�]��
	/// </summary>
	/// <param name="rot">������]��</param>
	const void SetStartAngle(const CQuaternion& rot) {
		m_StartRot = rot;
	}

private:
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
	bool Start()override final;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override final;
	
	CVector3 m_Pos = CVector3::Zero();					//�J�����̈ʒu
	CVector3 m_Target = CVector3::Zero();				//�J�����̒����_
	Player* m_player = nullptr;							//�v���C���[�̃|�C���^
	float m_AngleX = 0.0f;								//�J������X����]
	float m_AngleY = 0.0f;								//�J������Y����]
	CharacterController m_CharaCon;						//�L�����R��
	CQuaternion m_StartRot = CQuaternion::Identity();	//�J�����̏�����]��
	CVector3 PlayerCameraLeave = { 0.0f,100.0f,500.0f };//�J�����Ƃ̋���
	SpringCamera m_springCamera;						//�X�v�����O�J����
	float m_refleshTimer = 1.0f;						//�J�������čX�V���鎞��
};