#pragma once
#include "Archer/State/IArcherState.h"
class Archer;
/// <summary>
/// �A�[�`���[�����񂾂Ƃ��ɌĂ΂��֐�
/// �p�����g���ė��p����
/// </summary>
class ArcherDethState :
	public IArcherState
{
public :
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIArcherState�ɃA�[�`���[�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="ac">�A�[�`���[�|�C���^</param>
	ArcherDethState(Archer* ac) :
		IArcherState(ac) {

	}
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update() {};
	/// <summary>
	/// Hp�������������邩�ǂ���
	/// ����ł���̂ł���ȏ�Hp�͌��������Ȃ�
	/// </summary>
	/// <returns>����ł���̂�false��Ԃ�</returns>
	bool IsPossibleHpDown() {
		return false;
	}
};

