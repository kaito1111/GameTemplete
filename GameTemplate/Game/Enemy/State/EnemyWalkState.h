#pragma once
#include "Enemy/State/IEnemyState.h"
class Enemy;
/// <summary>
/// �X�P���g�����������ɌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class EnemyWalkState : public IEnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIEnemyState�ɃG�l�~�[�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="en">�G�l�~�[�̃|�C���^</param>
	EnemyWalkState(Enemy* en) :
		IEnemyState(en) {};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update() override;
};

