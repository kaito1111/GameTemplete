#pragma once

#include "Player/State/IPlayerState.h"
/// <summary>
/// �v���C���[���X�e�b�v���邽�тɌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class RollingState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	RollingState(Player* pl) :
		IPlayerState(pl)
	{

	}
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update() override;
	/// <summary>
	///	��]�ł��邩�ǂ���
	/// </summary>
	/// <returns>�o�b�N�X�e�b�v���ɂ���]���ł���l�ɂ���̂�true��Ԃ�</returns>
	bool IsPossibleRotate()const override
	{
		return true;
	}
};

