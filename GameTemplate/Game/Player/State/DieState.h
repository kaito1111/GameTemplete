#pragma once
#include "Player/State/IPlayerState.h"
#include "Player/DieSprite.h"
class ReSetGame;
class Fade;
/// <summary>
/// ���񂾂Ƃ��ɌĂ΂��N���X
/// �p�����g���Ďg�p����
/// </summary>
class DieState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	DieState(Player* player)
		:IPlayerState(player) {
	};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override final;
};

