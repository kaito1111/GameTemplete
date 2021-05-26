#pragma once
#include "Player/Player.h"
#include "level/Level.h"
class PlayerSpowner : public IGameObject
{
public:
	~PlayerSpowner() {};
	 
	//���x���Ń��[�h����t�@�C���p�X��Game�N���X�Őݒ�
	void SetFilePath(wchar_t* fileName) {
		wcscpy_s(m_filePath, fileName);
	}

	bool Start()override;
	void OnDestroy()override;

private:
	Player* m_player = nullptr;		//�v���C���[
	Level m_level;					//���x��
	wchar_t m_filePath[256] = {};	//���x���Ń��[�h����t�@�C���p�X
};

