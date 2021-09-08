#pragma once
#include "GameSceneFunction/Character.h"
/// <summary>
/// �A�j���[�V�����̏����𗘗p����N���X
/// �p�����g���ė��p����
/// </summary>
class Anime : public Character
{
public:
	/// <summary>
	/// �A�j���[�V�����N���b�v�ɃA�j���[�V�����f�[�^��ǂݍ��ފ֐�
	/// </summary>
	/// <param name="aniClip">�ǂݍ��܂������A�j���[�V�����N���b�v</param>
	/// <param name="filePath">
	/// �ǂݍ��ރt�@�C���p�X
	/// Assets/animeData/�͂���Ȃ�
	/// </param>
	void LoadAnimation(AnimationClip& aniClip,wchar_t* filePath);
	/// <summary>
	/// �A�j���[�V�����ɃA�j���[�V�����N���b�v��ǂݍ��ފ֐�
	/// </summary>
	/// <param name="aniClip">�ǂݍ��܂���A�j���[�V�����N���b�v</param>
	/// <param name="AnimationNum">�A�j���[�V�����̐�</param>
	void InitAnimation(AnimationClip aniClip[],int AnimationNum);
protected:
	Animation m_Animation;	//�A�j���[�V�����N���X
};

