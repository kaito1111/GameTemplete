#pragma once
#include "level/Level.h"
#include "Archer/Archer.h"
class ArcherSpowner final : public IGameObject
{
public:
	~ArcherSpowner() {};

	bool Start()override;
	void OnDestroy()override;

	void SetFilePath(const wchar_t* filePath) {
		wcscpy(m_filePath, filePath);
	}
private:
	Level m_level;
	std::vector<Archer*> m_ArcherList;
	wchar_t m_filePath[256] = {};
}; 

