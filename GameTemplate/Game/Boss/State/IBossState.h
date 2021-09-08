#pragma once
#include "Boss/Boss.h"
/// <summary>
/// �{�X�̃X�e�[�g�p�^�[���̃C���^�[�t�F�[�X�N���X
/// </summary>
class IBossState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIBossState�Ƀ{�X�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="boss">�{�X�̃|�C���^</param>
	IBossState(Boss* boss)
		: m_Boss(boss) 
	{};

	/// <summary>
	/// �C���X�^���X�����������ƁA��x�����Ă΂�鉼�z�J�n����
	/// </summary>
	virtual void Start() {};
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// �X�V�֐����g��Ȃ����͑�̂Ȃ��̂ŁA
	/// ���������āA��΂ɌĂԂ悤�ɂ��Ă���
	/// </summary>
	virtual void Update() = 0;


protected:
	Boss* m_Boss = nullptr;
};

