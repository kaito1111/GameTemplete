/*!
 *@brief	波形データバンク。
 */

#include "stdafx.h"
#include "sound/WaveFile.h"
#include "sound/WaveFileBank.h"
#include "util/Util.h"

WaveFileBank::WaveFileBank()
{
}
WaveFileBank::~WaveFileBank()
{
	ReleaseAll();
}
void WaveFileBank::Release(int groupID)
{
	for (auto waveFile : m_waveFileMap[groupID]) {
		waveFile.second->Release();
	}
	m_waveFileMap[groupID].clear();
}
void WaveFileBank::UnregistWaveFile(int groupID, WaveFilePtr waveFile)
{
	m_waveFileMap->erase(waveFile->GetFilePathHash());
}
void WaveFileBank::RegistWaveFile(int groupID, WaveFilePtr waveFile)
{
	m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
}
WaveFilePtr WaveFileBank::FindWaveFile(int groupID, const wchar_t* filePath)
{
	auto value = m_waveFileMap[groupID].find(Util::MakeHash(filePath));
	if (value != m_waveFileMap[groupID].end()) {
		return value->second;
	}
	return WaveFilePtr();
}