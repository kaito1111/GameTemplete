#pragma once

#include "Player/State/IPlayerState.h"

/// <summary>
/// �v���C���[���������Ă��Ȃ��Ƃ��ɌĂ΂��ҋ@�N���X�B
/// �p�����g���Ďg�p����
/// </summary>
class IdleState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	IdleState(Player* pl) :
		IPlayerState(pl)
	{

	}
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �ړ����邩����B
	/// </summary>
	/// <returns></returns>
	bool IsPossibleMove() const override
	{
		return false;
	}
};

