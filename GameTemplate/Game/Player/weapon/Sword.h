#pragma once
#include "Player/weapon/IWeapon.h"
/// <summary>
/// プレイヤーの剣クラス
/// </summary>
class Sword final: public IWeapon
{
public :
	/// <summary>
	/// 剣の初期化関数
	/// </summary>
	void Start()override final;
	/// <summary>
	/// 剣の更新関数
	/// </summary>
	void Update()override final;
	/// <summary>
	/// 剣の削除関数
	/// </summary>
	void Delete()override final;
};

