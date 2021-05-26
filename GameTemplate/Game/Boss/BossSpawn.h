#pragma once
#include "Level/Level.h"
class BossSpawn : public IGameObject
{
public: 
	~BossSpawn() {};//�f�X�g���N�^

	bool Start()override;//�������ʒu
	void OnDestroy()override;

	//level�f�[�^��ǂ݂���
	void SetFilePath(wchar_t* fileName) {
		wcscpy(m_FilePath, fileName);
	}

private:
	wchar_t m_FilePath[256];//���x���̃t�@�C���p�X
	Level m_Level;//���x���@

};

