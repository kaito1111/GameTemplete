#pragma once
#include "IArcherState.h"
class Archer;
/// <summary>
/// �A�[�`���[�̍U����Ԃ��Ǘ�����N���X
/// �p�����g���ė��p����
/// </summary>
class ArcherAttackState : public IArcherState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIArcherState�ɃA�[�`���[�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="a">�A�[�`���[�|�C���^</param>
	ArcherAttackState(Archer* a) :
		IArcherState(a) {};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
};

