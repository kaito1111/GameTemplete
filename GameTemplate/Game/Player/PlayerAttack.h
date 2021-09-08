#pragma once
#include "GameSceneFunction/Anime.h"

/// <summary>
/// �v���C�`���[���U������Ƃ��ɌĂ΂��N���X
/// </summary>
class PlayerAttack final : public IGameObject
{
public:
	/// <summary>
	/// �U���̃p�����[�^�����߂�֐�
	/// </summary>
	/// <param name="atack">�U����</param>
	/// <param name="aria">�U���͈�</param>
	/// <param name="pos">�U���ꏊ</param>
	void Init(float atack, float aria,const CVector3& pos) {
		m_Attack = atack;
		m_Aria = aria;
		m_AttackPos = pos;
	}

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
	bool Start();
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update();
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

	/// <summary>
	/// �����������ǂ���
	/// �P�x�������Ă�����U�����肪�Ȃ��Ȃ�
	/// </summary>
	/// <returns>true�œ�������</returns>
	bool IsHit() {
		return m_Hit;
	}
private:
	CVector3 m_AttackPos = CVector3::Zero();	//�U���ꏊ
	float m_Attack = 0.0f;						//�U����
	float m_Aria = 0.0f;						//�U���͈�
	bool m_Hit = false;							//�U�����P��q�b�g����
#ifdef _DEBUG
	SkinModelRender* m_AttackModel = nullptr;	//�U���͈͂�\�������f��
#endif
	SoundSource m_DamageSound;					//�U�����q�b�g������
};