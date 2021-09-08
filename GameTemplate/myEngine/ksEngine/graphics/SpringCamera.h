#pragma once
class Camera;
class SpringCamera
{
public:
	SpringCamera() {};
	~SpringCamera() {};
	void Init(Camera& camera, float moveMaxSpeed);

	/*!
	 * @brief	�ڕW�ƂȂ钍���_��ݒ�B
	 */
	void SetTarget(const CVector3& tar) {
		m_Target = tar;
	}

	/*!
	 * @brief	�ڕW�ƂȂ鎋�_��ݒ�B
	 */
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}

	/*!
	* @brief	�����ʂ�ݒ�B
	*/
	void SetFar(float _far)
	{
		if (m_camera == nullptr) {
			return;
		}
		m_camera->SetFar(_far);
	}

	/*!
	* @brief	�ߕ��ʂ�ݒ�B
	*/
	void SetNear(float _near)
	{
		if (m_camera == nullptr) {
			return;
		}
		m_camera->SetNear(_near);
	}
	/*!
	 *@brief	�ڕW�ƂȂ钍���_���擾�B
	 *@details
	 * ���̊֐����Ԃ��Ă��钍���_�́A���ۂ̒����_�ł͂Ȃ��̂Œ��ӂ��ĉ������B
	 * ���ۂ̒����_���ق����ꍇ��GetRealTarget���g�p���Ă��������B
	 */
	const CVector3& GetTarget() const
	{
		return m_Target;
	}
	/*!
	 *@brief	�ڕW�ƂȂ鎋�_���擾�B
	 *@details
	 * ���̊֐����Ԃ��Ă��鎋�_�́A���ۂ̎��_�ł͂Ȃ��̂Œ��ӂ��Ă��������B
	 * ���ۂ̎n�_���ق����ꍇ��GetRealPosition���g�p���ĉ������B
	 */
	const CVector3& GetPosition() const
	{
		return m_Position;
	}
	/*!
	* @brief	���ۂ̒����_���擾�B
	*/
	const CVector3& GetRealTarget() const
	{
		if (m_camera == nullptr) {
			return CVector3::Zero();
		}
		return m_camera->GetTarget();

	}
	/*!
	* @brief	���ۂ̎��_���擾�B
	*/
	const CVector3& GetRealPosition() const
	{
		if (m_camera == nullptr) {
			return CVector3::Zero();
		}
		return m_camera->GetPosition();
	}
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�J�������擾�B
	 */
	const Camera* GetCamera() const
	{
		return m_camera;
	}

	/*!
	* @brief	���t���b�V��
	*@details
	* ���̊֐����Ăяo���ƁA�o�l�̈ړ������t���b�V������āAUpdate�֐����Ăяo���ƃJ�����̈ʒu��
	* �����ɖڕW���_�ƖڕW�����_�Ɉړ����܂��B�V�[�����؂�ւ���ăJ��������C�ɐ؂�ւ������Ƃ��Ȃǂ�
	* �g�p���Ă��������B
	*/
	void Refresh()
	{
		m_TargetMoveSpeed = CVector3::Zero();
		m_PositionMoveSpeed = CVector3::Zero();
		m_isRefresh = true;
	}
	void SetViewAngle(float angle)
	{
		if (m_camera == nullptr) {
			return;
		}
		m_camera->SetViewAngle(angle);
	}
	float GetViewAngle() const
	{
		if (m_camera == nullptr) {
			return 0.0f;
		}
		return m_camera->GetViewAngle();
	}
private:
	Camera* m_camera = nullptr;
	CVector3 m_Target = CVector3::Zero();
	CVector3 m_Position = CVector3::Zero();
	CVector3 m_TargetMoveSpeed = CVector3::Zero();
	CVector3 m_PositionMoveSpeed = CVector3::Zero();
	float m_MaxMoveSpeed = 0.0f;
	float		m_targetDampingRate = 1.2f;				//!<�������B�l���傫���قǃJ�������x��t���Ă���B
	float		m_dampingRate = 1.2f;					//!<�������B
	float		m_dampingRateVel = 0.0f;
	bool m_isRefresh = false;
private:
	void UpdateSpringCamera();
	void UpdateCamera() {
		//�J�����̃A�b�v�f�[�g��GameObjectManajer��GameUpdate�ł��
		//if (m_camera != nullptr) {
		//	m_camera->Update();
		//}
	}
};
