#pragma once
#include "IBossState.h"
/// <summary>
/// �{�X���������ɌĂԃN���X
/// �p�����g���ė��p����
/// </summary>
class BossWalkState : public IBossState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIBossState�Ƀ{�X�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="boss">�{�X�̃|�C���^</param>
	BossWalkState(Boss* boss) :
		IBossState(boss) {};

	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
};

