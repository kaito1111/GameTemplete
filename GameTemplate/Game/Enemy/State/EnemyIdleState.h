#pragma once
#include "IEnemyState.h"
class Enemy;
/// <summary>
/// �X�P���g�����������Ă��Ȃ����ɌĂ΂��N���X
/// �p�����g���ė��p����
/// </summary>
class EnemyIdleState : public IEnemyState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// ���������ĂȂ����AIEnemyState�ɃG�l�~�[�̃|�C���^���m�ۂ��Ă���
	/// </summary>
	/// <param name="en">�G�l�~�[�̃|�C���^</param>
	EnemyIdleState(Enemy* en):
		IEnemyState(en) 
	{
	};
private:
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
};
