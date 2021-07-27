#pragma once
template<class T>
class ResourceManager
{
public:
	ResourceManager(){}
	~ResourceManager(){}

	void RegistResource(int nameKey, T* res) {
		m_resourceMap.insert(std::pair<int, T*>(nameKey, res));
	}
	T* GetResource(int nameKey)const {
		auto it = m_resourceMap.find(nameKey);
		if (it != m_resourceMap.end()) {
			return it->second;
		}
		return nullptr;
	}
	/// <summary>
	/// ƒŠƒ\[ƒX‚ğ‚·‚×‚Ä‰ğ•ú
	/// </summary>
	void Release() {
		for (auto& it : m_resourceMap) {
			it.second->Release();
		}
	}
private:
	std::map<int, T*> m_resourceMap;
};

