#pragma once
namespace ksEngine {
	typedef unsigned char GameObjectPrio;
	class IGameObject
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		IGameObject()
		{
		}
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~IGameObject() {

		}
	public:
		/// <summary>
		/// �`�揇�Ԃ�Ԃ�
		/// </summary>
		/// <returns>
		/// �`�揇��
		/// </returns>
		GameObjectPrio GetPriority()const {
			return m_priority;
		}

		/// <summary>
		/// �X�^�[�g�֐����������������ǂ����̃t���O��Ԃ�
		/// </summary>
		/// <returns>
		/// true���A���Ă�����A�����������B
		/// </returns>
		bool IsStart() {
			return m_IsStart;
		}
		
		/// <summary>
		/// ���S�t���O�𗧂Ă�B
		///���̃G���W�����O�ł͎g��Ȃ�
		/// </summary>
		void SetDeadMark() {
			m_IsDead = true;
		}
		
		/// <summary>
		/// DeleteGO���Ă΂ꂽ��
		/// �Ă΂ꂽ�ꍇ�͍X�V�Ȃǂ̊֐��������I�ɌĂ΂�Ȃ��Ȃ�
		///�܂莀��ł���Ƃ�������
	 	/// </summary>
		/// <returns>
		/// true���A���Ă�����A����ł��邱�ƂɂȂ�B
		/// </returns>
		bool IsDead()const {
			return m_IsDead;
		}

		/// <summary>
		/// �A�N�e�B�u�t���O��ݒ�
		/// m_IsDead�Ɏ��Ă��čX�V�Ȃǂ��Ăт����Ȃ����ȂǂɎg��
		/// �ł��A����ł͂��Ȃ�
		/// </summary>
		/// <param name="flag">�A�N�e�B�u�t���O</param>
		void SetActiveFlag(bool flag) {
			m_IsActive = flag;
		}
		
		/// <summary>
		/// �A�N�e�B�u�t���O���L�����ǂ���
		/// </summary>
		/// <returns>
		/// true���A���Ă�����A�A�N�e�B�u�t���O���L��
		/// </returns>
		bool IsActive()const {
			return m_IsActive;
		}

		/// <summary>
		/// �^�O��ݒ�
		/// </summary>
		/// <param name="tags">�^�O</param>
		void SetTag(unsigned int tags) {
			m_Tags = tags;
		}

		/// <summary>
		/// GameObject��New���ꂽ�Ƃ��ɌĂ�
		/// </summary>
		void SetMarkNewFromGameObjectManager() {
			m_IsNewFromGameObjectManajer = true;
		}
		/// <summary>
		/// GameObject��New���ꂽ�����擾
		/// </summary>
		/// <returns>
		/// true���A���Ă�����ANew����Ă���
		/// </returns>
		bool IsNewFromGameObjectManager() const {
			return m_IsNewFromGameObjectManajer;
		}

		/// <summary>
		/// Update�֐����ĂԂ��ǂ���
		/// true��Update���Ă�
		/// </summary>
		/// <param name="isUpdate">�A�b�v�f�[�g������</param>
		void SetUpdateFlag(bool isUpdate) {
			m_IsUpdate = isUpdate;
		}
	public:
		/// <summary>
		/// GameObjectManager�ɐς܂�Ă���C���X�^���X��Update���Ă�
		/// </summary>		
		void UpdateWrapper() {
			if (m_IsActive&&m_IsStart &&m_IsUpdate && !m_IsDead && !m_IsRegistDeadList) {
				//�X�V
				Update();
			}
		}
		/// <summary>
		/// GameObjectManager�ɐς܂�Ă���C���X�^���X�̃X�^�[�g���Ă�
		/// </summary>	
		void StartWrapper() {
			if (m_IsActive && !m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				if (Start()) {
					m_IsStart = true;
				}
			}
		}

		/// <summary>
		/// GameObjectManager�ɐς܂�Ă���C���X�^���X��Draw���Ă�
		/// </summary>	
		void DrawWrapper()
		{
			if (m_IsActive&&m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				Draw();
			}
		}

		/// <summary>
		/// GameObjectManager�ɐς܂�Ă���C���X�^���X��PostRender���Ă�
		/// </summary>	
		void PostRenderWrapper() {
			if (m_IsActive&&m_IsStart && !m_IsDead && !m_IsRegistDeadList) {
				PostRender();
			}
		}
	public:
		/// <summary>
		/// �C���X�^���X�����������ƁA��x�����Ă΂��J�n����
		/// </summary>
		/// <remarks>
		/// Unity��Start()�֐��̎d�l�ɏ����B
		/// </remarks>
		/// <returns>
		/// true���A���Ă�����A�����������B
		/// �����t���[���ɂ킽���ď��������������ꍇ�́A
		/// �����������܂�false��Ԃ��B
		/// </returns>
		virtual bool Start() { return true; };
		/// <summary>
		/// ���t���[���Ă΂��X�V�����B
		/// </summary>
		virtual	void Update() {};
		/// <summary>
		/// ���t���[���Ă΂��`�揈���B
		/// </summary>
		virtual void Draw() {};
		/// <summary>
		/// �C���X�^���X���j������鎞�ɌĂ΂��֐��B
		/// </summary>
		/// <remarks>
		/// �{�G���W���Ŏ������Ă���A�Q�[���I�u�W�F�N�g���폜����
		/// DeleteGO�֐��́A�����ɃC���X�^���X���폜����킯�ł͂Ȃ��A
		/// 1�t���[���x��ăC���X�^���X���폜�����B
		/// ���̂��߁A�f�X�g���N�^�̌Ăяo�����ADeleteGO�̌Ăяo������1�t���[���x��邱�ƂƂȂ�B
		/// DeleteGO���Ă΂ꂽ�^�C�~���O�ŁA�s�������I��������OnDestroy()�ɋL�q����B
		/// </remarks>
		virtual void OnDestroy() {};
		/// <summary>
		/// ���t���[���Ă΂��`�揈���B
		/// Draw�֐������Ă΂��^�C�~���O���x��
		/// </summary>
		virtual void PostRender() {};

		friend class GameObjectManager;
	protected:
		GameObjectPrio m_priority = 0;//���s�D��x
		bool m_IsStart = false;//�X�^�[�g�t���O
		bool m_IsUpdate = true;//�A�b�v�f�[�g�t���O
		bool m_IsDead = false;//�f�b�h�t���O
		bool m_IsActive = true;//�A�N�e�B�u�t���O
		bool m_IsRegistDeadList = false;//���S���X�g�ɐς܂�Ă��邩
		bool m_IsNewFromGameObjectManajer = false;//NewGO�ł���ꂽ��
		bool m_IsRegist = false;//GameObjectManager�ɂ܂�Ă��邩
		unsigned int m_Tags = false;//�^�O
		unsigned int m_nameKey = 0; //���O�L�[
	};
}

