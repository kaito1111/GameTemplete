#pragma once
#include "Player/weapon/IWeapon.h"
/// <summary>
/// �v���C���[�̌��N���X
/// </summary>
class Sword final: public IWeapon
{
public :
	/// <summary>
	/// ���̏������֐�
	/// </summary>
	void Start()override final;
	/// <summary>
	/// ���̍X�V�֐�
	/// </summary>
	void Update()override final;
	/// <summary>
	/// ���̍폜�֐�
	/// </summary>
	void Delete()override final;
};

