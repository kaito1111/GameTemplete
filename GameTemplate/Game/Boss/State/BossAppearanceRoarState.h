#pragma once
#include "IBossState.h"
/// <summary>
/// �{�X�̓o�ꎞ�Ɉ�x�����Ă΂��֐�
/// ���K�A�j���[�V�����𗬂�
/// �p�����g���ė��p����
/// </summary>
class BossAppearanceRoarState : public IBossState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIBossState�Ƀ{�X�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="boss">�{�X�̃|�C���^</param>
	BossAppearanceRoarState(Boss* boss) :
		IBossState(boss) {
	};
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;

private:
 };

