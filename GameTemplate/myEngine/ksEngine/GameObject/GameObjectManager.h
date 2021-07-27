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
	

		//Newを使ってGameObjectManajerに登録する関数
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
							//型変換がおかしい
							wchar_t errorMassage[256];
							swprintf_s(errorMassage, L"型変換に失敗しました。\nFindの型%s\nObjectName%s\n", typeid(T).name(), objectName);
							MessageBoxW(NULL, errorMassage, L"Findによるエラーメッセージ", MB_OK);
						}
						return p;
					}
				}
			}
			if (enableErrorMassage == true) {
				//名前確認して
				wchar_t errorMassage[256];
				swprintf_s(errorMassage, L"FindGO関数に指定された名前のインスタンスを見つけることができませんでした。\n名前が間違っていないか確認をして下さい。\n\n検索された名前 【%s】", objectName);
				MessageBoxW(NULL, errorMassage, L"Findによるエラーメッセージ", MB_OK);
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
		
		unsigned char			m_gameObjectPriorityMax = 32;				//!<ゲームオブジェクトの優先度の最大数。
		
		using GameObjectList = std::vector<IGameObject*>;
		

		std::vector<GameObjectList> m_GameObjectListArray;
		std::vector<GameObjectList> m_deleteObjectArray[2];
		int m_currentDeleteObjectBufferNo = 0;								//!<現在の削除オブジェクトのバッファ番号。

	public:
	};

	static inline GameObjectManager* CGameObjectManager() {
		return GameObjectManager::GetInstance();
	}
	/*!
	*@brief	ゲームオブジェクトの検索のヘルパー関数。
	*@details
	* 名前の検索が入るため遅いです。
	*@param[in]	objectName	ゲームオブジェクトの名前。
	*@param[in] enableErrorMessage	エラーメッセージが有効？
	*　呼び出し側でnullptrの判定を行いたい場合は、第二引数にfalseを指定して、エラーメッセージの処理を無効にしてください。
	*
	*@return 見つかったインスタンスのアドレス。見つからなかった場合はnullptrを返す。
	*/
	template<class T>
	static inline T* FindGO(const char* objectName, bool enableErrorMessage = true) {
		return CGameObjectManager()->FindGameObject<T>(objectName, enableErrorMessage);
	}

	/*!
	*@brief	ゲームオブジェクトの検索のヘルパー関数。
	*@details
	* 同名のゲームオブジェクトに全てに対して、クエリを行いたい場合に使用してください。
	*@param[in]	objectName	ゲームオブジェクトの名前。
	*@param[in]	func		ゲームオブジェクトが見つかったときに呼ばれるコールバック関数。
	*/
	template<class T>
	static inline void QueryGOs(const char* objectName, std::function<bool(T* go)>func) {
		CGameObjectManager()->FindGameObjects<T>(objectName, func);
	}
	/*!
	 *@brief	GameObjectでNewしてリストに積む
	 *@param[in]	int	ゲームオブジェクト。
	 *@param[in]	const char*	ゲームオブジェクト。
	 *@param[in]	objectName	オブジェクト名。(NULLの指定可）
	 */

	template<class T>
	T* NewGO(int priority, const char* objectName = nullptr) {
		return CGameObjectManager()->NewGameObject<T>((GameObjectPrio)priority, objectName);
	}
	/*!
	 *@brief	引数に持ってきたやつを消す
	 *@param[in]	IGameObject*	ゲームオブジェクト。
	 */
	static inline void DeleteGO(IGameObject* go)
	{
		CGameObjectManager()->DeleteGameObject(go);
	}

	/*!
	 *@brief	名前でヒットしたやつ消す
	 *@param[in]	objectName	ゲームオブジェクトの名前。
	 */
	static inline void DeleteGO(const char* ObjectName,bool enableErrorMessage=true) {
		IGameObject* go = FindGO<IGameObject>(ObjectName, enableErrorMessage);
		CGameObjectManager()->DeleteGameObject(go);
	}
	/*!
	 *@brief	名前でヒットしたやつ全部消す
	 *@param[in]	objectName	ゲームオブジェクトの名前。
	 */
	static inline void DeleteGOs(const char* ObjectName)
	{
		QueryGOs<IGameObject>(ObjectName, [](IGameObject* go) {
			DeleteGO(go);
			return true;
		});
	}
}