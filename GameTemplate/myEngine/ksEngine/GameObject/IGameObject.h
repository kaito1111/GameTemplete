#pragma once
namespace ksEngine {
	typedef unsigned char GameObjectPrio;
	class IGameObject
	{
	public:
		IGameObject()
		{
		}
		virtual ~IGameObject() {

		}
	public:
		GameObjectPrio GetPriority()const {
			return m_priority;
		}
		//スタート関数が終わった？
		bool IsStart() {
			return m_IsStart;
		}
		//死亡フラグを立てる。
		//このエンジンより外では使わない
		void SetDeadMark() {
			m_IsDead = true;
		}
		//死亡判定
		bool IsDead()const {
			return m_IsDead;
		}
		//アクティブフラグを設定
		void SetActiveFlag(bool flag) {
			m_IsActive = flag;
		}
		//アクティブか？
		bool IsActive()const {
			return m_IsActive;
		}
		//タグを設定
		void SetTag(unsigned int tags) {
			m_Tags = tags;
		}
		//GameObjectでNewされたときに呼ぶ
		void SetMarkNewFromGameObjectManager() {
			m_IsNewFromGameObjectManajer = true;
		}
		//GameObjectでNewされたかを取得
		bool IsNewFromGameObjectManager() const {
			return m_IsNewFromGameObjectManajer;
		}
	public:
		void UpdateWrapper() {
			if (m_IsActive&&m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				Update();
			}
		}
		void StartWrapper() {
			if (m_IsActive && !m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				if (Start()) {
					m_IsStart = true;
				}
			}
		}
		void DrawWrapper()
		{
			if (m_IsActive&&m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				Draw();
			}
		}

		void PostRenderWrapper() {
			if (m_IsActive&&m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				PostRender();
			}
		}
	public:
		virtual bool Start() { return true; };
		virtual	void Update() {};
		virtual void Draw() {};
		virtual void OnDestroy() {};
		virtual void PostRender() {};

		friend class GameObjectManager;
	protected:
		GameObjectPrio m_priority = 0;//実行優先度
		bool m_IsStart = false;//スタートフラグ
		bool m_IsDead = false;//デッドフラグ
		bool m_IsActive = true;//アクティブフラグ
		bool m_IsRegistDeadList = false;//死亡リストに積まれているか
		bool m_IsNewFromGameObjectManajer = false;//NewGOでつくられたか
		bool m_IsRegist = false;//GameObjectManagerにつまれているか
		unsigned int m_Tags = false;//タグ
		unsigned int m_nameKey = 0; //名前キー
	};
}

