#pragma once
#include "Player/State/IPlayerState.h"
class Player;
/// <summary>
/// �^�C�g����ʂőҋ@���Ă���Ƃ��ɌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class TitleState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	TitleState(Player* pl) :IPlayerState (pl){};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
};

