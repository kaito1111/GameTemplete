#pragma once
#include "GameSceneFunction/Character.h"
/// <summary>
/// アニメーションの処理を利用するクラス
/// 継承を使って利用する
/// </summary>
class Anime : public Character
{
public:
	/// <summary>
	/// アニメーションクリップにアニメーションデータを読み込む関数
	/// </summary>
	/// <param name="aniClip">読み込ませたいアニメーションクリップ</param>
	/// <param name="filePath">
	/// 読み込むファイルパス
	/// Assets/animeData/はいらない
	/// </param>
	void LoadAnimation(AnimationClip& aniClip,wchar_t* filePath);
	/// <summary>
	/// アニメーションにアニメーションクリップを読み込む関数
	/// </summary>
	/// <param name="aniClip">読み込ませるアニメーションクリップ</param>
	/// <param name="AnimationNum">アニメーションの数</param>
	void InitAnimation(AnimationClip aniClip[],int AnimationNum);
protected:
	Animation m_Animation;	//アニメーションクラス
};

