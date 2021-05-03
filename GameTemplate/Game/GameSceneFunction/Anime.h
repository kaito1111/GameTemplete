#pragma once
#include "GameSceneFunction/Character.h"
class Anime : public Character
{
public:
	~Anime() {};

	//Assets/animeData/‚Í‚¢‚ç‚È‚¢
	void LoadAnimation(AnimationClip& aniClip,wchar_t* filePath);

	void InitAnimation(AnimationClip aniClip[],int AnimationNum);
protected:
	Animation m_Animation;
};

