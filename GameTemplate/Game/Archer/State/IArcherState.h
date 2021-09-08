#pragma once
class Archer;
/// <summary>
/// �A�[�`���[�̃X�e�[�g�p�^�[���̃C���^�[�t�F�[�X�N���X
/// </summary>
class IArcherState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// �A�[�`���[�|�C���^�����̊֐��Ŋm�ۂ���
	/// </summary>
	/// <param name="a">�A�[�`���[�|�C���^</param>
	IArcherState(Archer* a):
	m_Archer(a){};
	/// <summary>
	///�f�X�g���N�^�̉��z�֐�
	/// </summary>
	virtual ~IArcherState() {};
	/// <summary>
	/// �C���X�^���X�����������ƁA��x�����Ă΂�鉼�z�J�n����
	/// </summary>
	virtual void Start();
	/// <summary>
	/// ���t���[���Ă΂�鉼�z�X�V�����B
	/// </summary>
	virtual void Update();
	/// <summary>
	/// HP�������������邩��Ԃ��֐�
	/// </summary>
	/// <returns>true��Ԃ����ƂŌ��������邱�Ƃ��ł���</returns>
	virtual bool IsPossibleHpDown() {
		return true;
	};
protected:
	Archer* m_Archer = nullptr;
};

