#include "pch.h"
#include "Anime.h"

void Anime::LoadAnimation(AnimationClip& aniClip, wchar_t* filePath)
{
	wchar_t AssetsFile[256] = L"Assets/animData/";
	wcscat(AssetsFile, filePath);
	aniClip.Load(AssetsFile);
}

void Anime::InitAnimation(AnimationClip aniClip[],int AnimationNum)
{
	m_Animation.Init(m_Model->GetModel(), aniClip, AnimationNum);
}