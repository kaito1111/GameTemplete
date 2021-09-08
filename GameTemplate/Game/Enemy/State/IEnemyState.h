#pragma once
class Enemy;
/// <summary>
/// �X�P���g���̃X�e�[�g�p�^�[���̃C���^�[�t�F�[�X�N���X
/// </summary>
class IEnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// �G�l�~�[�̃|�C���^�����̊֐��Ŋm�ۂ���
	/// </summary>
	/// <param name="en">�G�l�~�[�̃|�C���^</param>
	IEnemyState(Enemy* en) :
		m_enemy(en) 
	{
	};
	/// <summary>
	///�f�X�g���N�^�̉��z�֐�
	/// </summary>
	virtual ~IEnemyState() {};
	/// <summary>
	/// ���t���[���Ă΂�鉼�z�X�V�����B
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// HP�������������邩��Ԃ��֐�
	/// </summary>
	/// <returns>true��Ԃ����ƂŌ��������邱�Ƃ��ł���</returns>
	virtual bool IsPossibleHpDown() {
		return true;
	}
private:	
	/// <summary>
	/// �ړ��\���ǂ�����Ԃ��֐�
	/// </summary>
	/// <returns>true�ňړ��\</returns>
	virtual bool IsPossibleMove() const {
		return true;
	}
	/// <summary>
	/// ��]�\���ǂ�����Ԃ��֐�
	/// </summary>
	/// <returns>ture�ŉ�]�\</returns>
	virtual bool IsPossibleRotate()const {
		return true;
	}

protected:
	Enemy* m_enemy = nullptr;	//�G�l�~�[�|�C���^
};

