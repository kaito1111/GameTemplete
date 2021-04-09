#include "pch.h"
#include "ArcherSpowner.h"
#include "Archer/Archer.h"

bool ArcherSpowner::Start()
{
	m_level.Init(m_filePath, [&](LevelObjectData object)->bool{
		if (wcscmp(L"Archer", object.name) == 0) {
			Archer* archer = NewGO<Archer>(0);
			archer->SetSpownPosition(object.position);
			archer->SetRotation(object.rotation);
			m_ArcherList.push_back(archer);
		}
		return true;
	});
	return true;
}

void ArcherSpowner::OnDestroy()
{
	for (auto& archer : m_ArcherList) {
		DeleteGO(archer);
	}
}
