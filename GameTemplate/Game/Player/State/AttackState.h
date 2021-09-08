#pragma once
#include "Player/State/IPlayerState.h"
class Player;
/// <summary>
/// �v���C���[���U�����邽�тɌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class AttackState :	public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	AttackState(Player* pl) :
		IPlayerState(pl) {

	}
	~AttackState() {};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
	/// <summary>
	///	��]�ł��邩�ǂ���
	/// </summary>
	/// <returns>�U�����͉�]���ł���̂�true��Ԃ�</returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

