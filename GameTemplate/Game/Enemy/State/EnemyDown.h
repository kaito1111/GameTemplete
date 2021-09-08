#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
/// <summary>
/// �X�P���g�������ʂƌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class EnemyDown : public IEnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIEnemyState�ɃG�l�~�[�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="en">�G�l�~�[�̃|�C���^</param>
	EnemyDown(Enemy* en) :
		IEnemyState(en) {};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// Hp�������������邩�ǂ���
	/// ����ł���̂ł���ȏ�Hp�͌��������Ȃ�
	/// </summary>
	/// <returns>����ł���̂�false��Ԃ�</returns>
	bool IsPossibleHpDown() {
		return false;
	}
};

