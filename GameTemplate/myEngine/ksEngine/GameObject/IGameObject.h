#pragma once
namespace ksEngine {
	typedef unsigned char GameObjectPrio;
	class IGameObject
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		IGameObject()
		{
		}
		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~IGameObject() {

		}
	public:
		/// <summary>
		/// 描画順番を返す
		/// </summary>
		/// <returns>
		/// 描画順番
		/// </returns>
		GameObjectPrio GetPriority()const {
			return m_priority;
		}

		/// <summary>
		/// スタート関数が完了したかをどうかのフラグを返す
		/// </summary>
		/// <returns>
		/// trueが帰ってきたら、初期化完了。
		/// </returns>
		bool IsStart() {
			return m_IsStart;
		}
		
		/// <summary>
		/// 死亡フラグを立てる。
		///このエンジンより外では使わない
		/// </summary>
		void SetDeadMark() {
			m_IsDead = true;
		}
		
		/// <summary>
		/// DeleteGOが呼ばれたか
		/// 呼ばれた場合は更新などの関数が自動的に呼ばれなくなる
		///つまり死んでいるということ
	 	/// </summary>
		/// <returns>
		/// trueが帰ってきたら、死んでいることになる。
		/// </returns>
		bool IsDead()const {
			return m_IsDead;
		}

		/// <summary>
		/// アクティブフラグを設定
		/// m_IsDeadに似ていて更新などを呼びたくない時などに使う
		/// でも、死んではいない
		/// </summary>
		/// <param name="flag">アクティブフラグ</param>
		void SetActiveFlag(bool flag) {
			m_IsActive = flag;
		}
		
		/// <summary>
		/// アクティブフラグが有効かどうか
		/// </summary>
		/// <returns>
		/// trueが帰ってきたら、アクティブフラグが有効
		/// </returns>
		bool IsActive()const {
			return m_IsActive;
		}

		/// <summary>
		/// タグを設定
		/// </summary>
		/// <param name="tags">タグ</param>
		void SetTag(unsigned int tags) {
			m_Tags = tags;
		}

		/// <summary>
		/// GameObjectでNewされたときに呼ぶ
		/// </summary>
		void SetMarkNewFromGameObjectManager() {
			m_IsNewFromGameObjectManajer = true;
		}
		/// <summary>
		/// GameObjectでNewされたかを取得
		/// </summary>
		/// <returns>
		/// trueが帰ってきたら、Newされている
		/// </returns>
		bool IsNewFromGameObjectManager() const {
			return m_IsNewFromGameObjectManajer;
		}

		/// <summary>
		/// Update関数を呼ぶかどうか
		/// trueでUpdateを呼ぶ
		/// </summary>
		/// <param name="isUpdate">アップデートをする</param>
		void SetUpdateFlag(bool isUpdate) {
			m_IsUpdate = isUpdate;
		}
	public:
		/// <summary>
		/// GameObjectManagerに積まれているインスタンスのUpdateを呼ぶ
		/// </summary>		
		void UpdateWrapper() {
			if (m_IsActive&&m_IsStart &&m_IsUpdate && !m_IsDead && !m_IsRegistDeadList) {
				//更新
				Update();
			}
		}
		/// <summary>
		/// GameObjectManagerに積まれているインスタンスのスタートを呼ぶ
		/// </summary>	
		void StartWrapper() {
			if (m_IsActive && !m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				if (Start()) {
					m_IsStart = true;
				}
			}
		}

		/// <summary>
		/// GameObjectManagerに積まれているインスタンスのDrawを呼ぶ
		/// </summary>	
		void DrawWrapper()
		{
			if (m_IsActive&&m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				Draw();
			}
		}

		/// <summary>
		/// GameObjectManagerに積まれているインスタンスのPostRenderを呼ぶ
		/// </summary>	
		void PostRenderWrapper() {
			if (m_IsActive&&m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				PostRender();
			}
		}
	public:
		/// <summary>
		/// インスタンスが生成されると、一度だけ呼ばれる開始処理
		/// </summary>
		/// <remarks>
		/// UnityのStart()関数の仕様に準拠。
		/// </remarks>
		/// <returns>
		/// trueが帰ってきたら、初期化完了。
		/// 複数フレームにわたって初期化をしたい場合は、
		/// 初期化完了までfalseを返す。
		/// </returns>
		virtual bool Start() { return true; };
		/// <summary>
		/// 毎フレーム呼ばれる更新処理。
		/// </summary>
		virtual	void Update() {};
		/// <summary>
		/// 毎フレーム呼ばれる描画処理。
		/// </summary>
		virtual void Draw() {};
		/// <summary>
		/// インスタンスが破棄される時に呼ばれる関数。
		/// </summary>
		/// <remarks>
		/// 本エンジンで実装している、ゲームオブジェクトを削除する
		/// DeleteGO関数は、すぐにインスタンスを削除するわけではなく、
		/// 1フレーム遅れてインスタンスが削除される。
		/// そのため、デストラクタの呼び出しが、DeleteGOの呼び出しから1フレーム遅れることとなる。
		/// DeleteGOが呼ばれたタイミングで、行いたい終了処理はOnDestroy()に記述する。
		/// </remarks>
		virtual void OnDestroy() {};
		/// <summary>
		/// 毎フレーム呼ばれる描画処理。
		/// Draw関数よりも呼ばれるタイミングが遅い
		/// </summary>
		virtual void PostRender() {};

		friend class GameObjectManager;
	protected:
		GameObjectPrio m_priority = 0;//実行優先度
		bool m_IsStart = false;//スタートフラグ
		bool m_IsUpdate = true;//アップデートフラグ
		bool m_IsDead = false;//デッドフラグ
		bool m_IsActive = true;//アクティブフラグ
		bool m_IsRegistDeadList = false;//死亡リストに積まれているか
		bool m_IsNewFromGameObjectManajer = false;//NewGOでつくられたか
		bool m_IsRegist = false;//GameObjectManagerにつまれているか
		unsigned int m_Tags = false;//タグ
		unsigned int m_nameKey = 0; //名前キー
	};
}

