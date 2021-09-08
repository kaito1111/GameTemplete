#pragma once
#include "Player/State/IPlayerState.h"
class Player;
class GameStart;
/// <summary>
/// �^�C�g����ʂ���Q�[����ʂɈڍs���鎞�̏��
/// �p�����g���Ďg�p����
/// </summary>
class StandingState : public IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIPlayerState�Ƀv���C���[�|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="pl">�v���C���[�|�C���^</param>
	StandingState(Player* pl) :IPlayerState(pl) {

	}
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
	GameStart* m_GameStart = nullptr;		//�Q�[���V�[���ɑJ�ڂ���N���X�̃|�C���^
};

