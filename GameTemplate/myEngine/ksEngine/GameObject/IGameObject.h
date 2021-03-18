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
		//�X�^�[�g�֐����I������H
		bool IsStart() {
			return m_IsStart;
		}
		//���S�t���O�𗧂Ă�B
		//���̃G���W�����O�ł͎g��Ȃ�
		void SetDeadMark() {
			m_IsDead = true;
		}
		//���S����
		bool IsDead()const {
			return m_IsDead;
		}
		//�A�N�e�B�u�t���O��ݒ�
		void SetActiveFlag(bool flag) {
			m_IsActive = flag;
		}
		//�A�N�e�B�u���H
		bool IsActive()const {
			return m_IsActive;
		}
		//�^�O��ݒ�
		void SetTag(unsigned int tags) {
			m_Tags = tags;
		}
		//GameObject��New���ꂽ�Ƃ��ɌĂ�
		void SetMarkNewFromGameObjectManager() {
			m_IsNewFromGameObjectManajer = true;
		}
		//GameObject��New���ꂽ�����擾
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
		GameObjectPrio m_priority = 0;//���s�D��x
		bool m_IsStart = false;//�X�^�[�g�t���O
		bool m_IsDead = false;//�f�b�h�t���O
		bool m_IsActive = true;//�A�N�e�B�u�t���O
		bool m_IsRegistDeadList = false;//���S���X�g�ɐς܂�Ă��邩
		bool m_IsNewFromGameObjectManajer = false;//NewGO�ł���ꂽ��
		bool m_IsRegist = false;//GameObjectManager�ɂ܂�Ă��邩
		unsigned int m_Tags = false;//�^�O
		unsigned int m_nameKey = 0; //���O�L�[
	};
}

