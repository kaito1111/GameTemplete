#pragma once
#include "IGameObject.h"
#include "util/Util.h"
namespace ksEngine {
	using IGameObjectPtr = std::shared_ptr<IGameObject>;
	using IGameObjectWeakPtr = std::weak_ptr<IGameObject>;
	typedef std::shared_ptr<IGameObject>& uniIGameObject;
	class GameObjectManager
	{
	public:
	
		GameObjectManager();
		~GameObjectManager();
	private:
		static unsigned int MakeObjectNameKey(const char*objectName) {
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");
			unsigned int hash;
			if (objectName == nullptr) {
				hash = defaultNameKey;
			}
			else {
				hash = Util::MakeHash(objectName);
			}
			return hash;
		}
	private:
		void Start();
		void Update();
		void Draw();
		void PostRender();
		void ExecuteDeleteGameObject();
	public:
	

		//New���g����GameObjectManajer�ɓo�^����֐�
		template<class T>
		T* NewGameObject(GameObjectPrio prio, const char* objectName) {
			(void)objectName;
			min(prio, m_gameObjectPriorityMax);
			T* NewObject = new T();
			
			NewObject->SetMarkNewFromGameObjectManager();
			
			unsigned int hash = MakeObjectNameKey(objectName);
			NewObject->m_IsRegist = true;
			NewObject->m_priority = prio;
			NewObject->m_nameKey = hash;
			
			m_GameObjectListArray.at(prio).push_back(NewObject);
			return NewObject;
		}
		void DeleteGameObject(IGameObject* go)
		{
			if (go!= nullptr&&
				go->m_IsRegist) {
				go->SetDeadMark();
				go->OnDestroy();
				go->m_IsRegist = false;
				go->m_IsRegistDeadList = true;
				m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(go->GetPriority()).push_back(go);
				go = nullptr;
			}
		}
		template<class T>
		T* FindGameObject(const char* objectName, bool enableErrorMassage) {
			unsigned int NameKey = Util::MakeHash(objectName);
			for (GameObjectList goList : m_GameObjectListArray) {
				for (IGameObject* go : goList) {
					if (go->m_nameKey == NameKey) {
						T* p = dynamic_cast<T*>(go);
						if (p == nullptr&&enableErrorMassage == true) {
							//�^�ϊ�����������
							wchar_t errorMassage[256];
							swprintf_s(errorMassage, L"�^�ϊ��Ɏ��s���܂����B\nFind�̌^%s\nObjectName%s\n", typeid(T).name(), objectName);
							MessageBoxW(NULL, errorMassage, L"Find�ɂ��G���[���b�Z�[�W", MB_OK);
						}
						return p;
					}
				}
			}
			if (enableErrorMassage == true) {
				//���O�m�F����
				wchar_t errorMassage[256];
				swprintf_s(errorMassage, L"FindGO�֐��Ɏw�肳�ꂽ���O�̃C���X�^���X�������邱�Ƃ��ł��܂���ł����B\n���O���Ԉ���Ă��Ȃ����m�F�����ĉ������B\n\n�������ꂽ���O �y%s�z", objectName);
				MessageBoxW(NULL, errorMassage, L"Find�ɂ��G���[���b�Z�[�W", MB_OK);
			}
			return nullptr;
		}
		template<class T>
		void FindGameObjects(const char* objectName, std::function<bool(T* go)>func) {
			unsigned int namekey = Util::MakeHash(objectName);
			for (auto GOList : m_GameObjectListArray) {
				for (auto go : GOList) {
					if (go->m_nameKey == namekey) {
						T* p = dynamic_cast<T*>(go);
						if (func(p) == false) {
							return ;
						}
					}
				}
			}
		}

		void FindGameObjectWithTag(unsigned int tags, std::function<void(IGameObject* go)> func) {
			for (GameObjectList GOList : m_GameObjectListArray) {
				for (IGameObject* go : GOList) {
					unsigned int Tags = go->m_Tags;
					if ((Tags&tags) != 0) {
						func(go);
					}

				}
			}
		}
		void ExcuteGame();
	public:
		static GameObjectManager* GetInstance() {
			static GameObjectManager instance;
			return &instance;
		}
		void Init();

	private:
		
		unsigned char			m_gameObjectPriorityMax = 32;				//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B
		
		using GameObjectList = std::vector<IGameObject*>;
		

		std::vector<GameObjectList> m_GameObjectListArray;
		std::vector<GameObjectList> m_deleteObjectArray[2];
		int m_currentDeleteObjectBufferNo = 0;								//!<���݂̍폜�I�u�W�F�N�g�̃o�b�t�@�ԍ��B

	public:
	};

	static inline GameObjectManager* CGameObjectManager() {
		return GameObjectManager::GetInstance();
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
	*@details
	* ���O�̌��������邽�ߒx���ł��B
	*@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
	*@param[in] enableErrorMessage	�G���[���b�Z�[�W���L���H
	*�@�Ăяo������nullptr�̔�����s�������ꍇ�́A��������false���w�肵�āA�G���[���b�Z�[�W�̏����𖳌��ɂ��Ă��������B
	*
	*@return ���������C���X�^���X�̃A�h���X�B������Ȃ������ꍇ��nullptr��Ԃ��B
	*/
	template<class T>
	static inline T* FindGO(const char* objectName, bool enableErrorMessage = true) {
		return CGameObjectManager()->FindGameObject<T>(objectName, enableErrorMessage);
	}

	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
	*@details
	* �����̃Q�[���I�u�W�F�N�g�ɑS�Ăɑ΂��āA�N�G�����s�������ꍇ�Ɏg�p���Ă��������B
	*@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
	*@param[in]	func		�Q�[���I�u�W�F�N�g�����������Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	*/
	template<class T>
	static inline void QueryGOs(const char* objectName, std::function<bool(T* go)>func) {
		CGameObjectManager()->FindGameObjects<T>(objectName, func);
	}
	/*!
	 *@brief	GameObject��New���ă��X�g�ɐς�
	 *@param[in]	int	�Q�[���I�u�W�F�N�g�B
	 *@param[in]	const char*	�Q�[���I�u�W�F�N�g�B
	 *@param[in]	objectName	�I�u�W�F�N�g���B(NULL�̎w��j
	 */

	template<class T>
	T* NewGO(int priority, const char* objectName = nullptr) {
		return CGameObjectManager()->NewGameObject<T>((GameObjectPrio)priority, objectName);
	}
	/*!
	 *@brief	�����Ɏ����Ă����������
	 *@param[in]	IGameObject*	�Q�[���I�u�W�F�N�g�B
	 */
	static inline void DeleteGO(IGameObject* go)
	{
		CGameObjectManager()->DeleteGameObject(go);
	}

	/*!
	 *@brief	���O�Ńq�b�g���������
	 *@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
	 */
	static inline void DeleteGO(const char* ObjectName,bool enableErrorMessage=true) {
		IGameObject* go = FindGO<IGameObject>(ObjectName, enableErrorMessage);
		CGameObjectManager()->DeleteGameObject(go);
	}
	/*!
	 *@brief	���O�Ńq�b�g������S������
	 *@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
	 */
	static inline void DeleteGOs(const char* ObjectName)
	{
		QueryGOs<IGameObject>(ObjectName, [](IGameObject* go) {
			DeleteGO(go);
			return true;
		});
	}
}