#pragma once
class Player;

/// <summary>
/// �v���C���[�̃X�e�[�g�p�^�[���̃C���^�[�t�F�[�X�N���X
/// </summary>
class IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// �v���C���[�̃|�C���^�����̊֐��Ŋm�ۂ���
	/// </summary>
	/// <param name="pl">�v���C���[�̃|�C���^</param>
	IPlayerState(Player* pl) :
		m_player(pl){}

	virtual ~IPlayerState(){}
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// �X�V�֐����g��Ȃ����͑�̂Ȃ��̂ŁA
	/// ���������āA��΂ɌĂԂ悤�ɂ��Ă���
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �ړ��\���ǂ�����Ԃ����z�֐�
	/// </summary>
	/// <returns>true��Ԃ��ƈړ��ł���</returns>
	virtual bool IsPossibleMove() const
	{
		return true;
	}
	/// <summary>
	/// ��]�\���ǂ�����Ԃ����z�֐�
	/// </summary>
	/// <returns>true��Ԃ��Ɖ�]�ł���</returns>
	virtual bool IsPossibleRotate() const
	{
		return false;
	}
protected:
	Player* m_player = nullptr;	//�v���C���[�|�C���^�B
};

