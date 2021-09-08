#pragma once
#include "PLayer/State/IPlayerState.h"
class Player;
/// <summary>
/// ���[�����O�A�^�b�N������ƌĂ΂��֐�
/// �p�����g���ė��p����
/// </summary>
class RollingAttackState : public IPlayerState
{
public: 
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	RollingAttackState(Player* pl) :
		IPlayerState(pl)
	{

	}
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
	/// <summary>
	/// <summary>
	///	��]�ł��邩�ǂ���
	/// </summary>
	/// <returns>�U�����͉�]���ł���̂�true��Ԃ�</returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

