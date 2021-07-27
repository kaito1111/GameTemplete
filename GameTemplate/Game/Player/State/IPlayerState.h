#pragma once
class Player;

/// <summary>
/// �v���C���[�̏�Ԃ̊��N���X�B
/// </summary>
class IPlayerState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pl">�v���C���[</param>
	IPlayerState(Player* pl) :
		m_player(pl){}

	virtual ~IPlayerState(){}
	/// <summary>
	/// �X�V�����B
	/// </summary>
	virtual void Update() = 0;
	virtual void Delete(){}
	/// <summary>
	/// �ړ��\�����肷��B
	/// </summary>
	virtual bool IsPossibleMove() const
	{
		return true;
	}
	/// <summary>
	/// ��]�ł��邩���肷��H
	/// </summary>
	/// <returns></returns>
	virtual bool IsPossibleRotate() const
	{
		return false;
	}
protected:
	Player* m_player = nullptr;	//�v���C���[�B
};

