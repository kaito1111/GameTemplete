#pragma once
#include "Player/State/IPlayerState.h"
class Player;
/// <summary>
///�v���C���[���_���[�W���󂯂�ƌĂ΂��N���X
/// �p�����g���Ďg�p����
/// </summary>
class DamageState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	DamageState(Player* pl) :
		IPlayerState(pl) {};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
};