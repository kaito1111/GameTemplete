#pragma once
#include "IBossState.h"
/// <summary>
/// �{�X�����K������Ƃ��ɌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class BossNormalRoar:public IBossState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIBossState�Ƀ{�X�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="boss">�{�X�̃|�C���^</param>
	BossNormalRoar(Boss* boss) :
		IBossState(boss) {
	};

	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;

private:
};

