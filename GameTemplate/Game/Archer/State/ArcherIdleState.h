#pragma once
#include "Archer/Archer.h"

/// <summary>
/// �A�[�`���[���ҋ@��ԂɌĂ΂��֐�
/// �p�����g���ė��p����
/// </summary>
class ArcherIdleState : public IArcherState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// IArcherState��Archer�̃|�C���^��n���Ă���
	/// </summary>
	/// <param name="a">�A�[�`���[�|�C���^</param>
	ArcherIdleState(Archer* a) :
		IArcherState(a){}
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
};

