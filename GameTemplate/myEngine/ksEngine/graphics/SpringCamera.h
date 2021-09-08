#pragma once
class Camera;
class SpringCamera
{
public:
	SpringCamera() {};
	~SpringCamera() {};
	void Init(Camera& camera, float moveMaxSpeed);

	/*!
	 * @brief	目標となる注視点を設定。
	 */
	void SetTarget(const CVector3& tar) {
		m_Target = tar;
	}

	/*!
	 * @brief	目標となる視点を設定。
	 */
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}

	/*!
	* @brief	遠平面を設定。
	*/
	void SetFar(float _far)
	{
		if (m_camera == nullptr) {
			return;
		}
		m_camera->SetFar(_far);
	}

	/*!
	* @brief	近平面を設定。
	*/
	void SetNear(float _near)
	{
		if (m_camera == nullptr) {
			return;
		}
		m_camera->SetNear(_near);
	}
	/*!
	 *@brief	目標となる注視点を取得。
	 *@details
	 * この関数が返してくる注視点は、実際の注視点ではないので注意して下さい。
	 * 実際の注視点がほしい場合はGetRealTargetを使用してください。
	 */
	const CVector3& GetTarget() const
	{
		return m_Target;
	}
	/*!
	 *@brief	目標となる視点を取得。
	 *@details
	 * この関数が返してくる視点は、実際の視点ではないので注意してください。
	 * 実際の始点がほしい場合はGetRealPositionを使用して下さい。
	 */
	const CVector3& GetPosition() const
	{
		return m_Position;
	}
	/*!
	* @brief	実際の注視点を取得。
	*/
	const CVector3& GetRealTarget() const
	{
		if (m_camera == nullptr) {
			return CVector3::Zero();
		}
		return m_camera->GetTarget();

	}
	/*!
	* @brief	実際の視点を取得。
	*/
	const CVector3& GetRealPosition() const
	{
		if (m_camera == nullptr) {
			return CVector3::Zero();
		}
		return m_camera->GetPosition();
	}
	/*!
	 * @brief	更新。
	 */
	void Update();
	/*!
	 * @brief	カメラを取得。
	 */
	const Camera* GetCamera() const
	{
		return m_camera;
	}

	/*!
	* @brief	リフレッシュ
	*@details
	* この関数を呼び出すと、バネの移動がリフレッシュされて、Update関数を呼び出すとカメラの位置が
	* 即座に目標視点と目標注視点に移動します。シーンが切り替わってカメラを一気に切り替えたいときなどに
	* 使用してください。
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
	float		m_targetDampingRate = 1.2f;				//!<減衰率。値が大きいほどカメラが遅れ付いてくる。
	float		m_dampingRate = 1.2f;					//!<減衰率。
	float		m_dampingRateVel = 0.0f;
	bool m_isRefresh = false;
private:
	void UpdateSpringCamera();
	void UpdateCamera() {
		//カメラのアップデートはGameObjectManajerのGameUpdateでやる
		//if (m_camera != nullptr) {
		//	m_camera->Update();
		//}
	}
};
