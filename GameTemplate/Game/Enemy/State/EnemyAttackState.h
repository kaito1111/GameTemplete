#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
/// <summary>
/// �X�P���g�����U�����鎞�ɌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class EnemyAttackState : public IEnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIEnemyState�ɃG�l�~�[�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="en">�G�l�~�[�̃|�C���^</param>
	EnemyAttackState(Enemy* en) :
		IEnemyState(en) {}
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
};

