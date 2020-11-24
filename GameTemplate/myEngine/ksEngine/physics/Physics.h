#pragma once


class RigidBody;

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		m_collisionConfig = nullptr;
	btCollisionDispatcher*					m_collisionDispatcher = nullptr;	//!<衝突解決処理。
	btBroadphaseInterface*					m_overlappingPairCache = nullptr;	//!<ブロードフェーズ。衝突判定の枝切り。
	btSequentialImpulseConstraintSolver*	m_constraintSolver = nullptr;		//!<コンストレイントソルバー。拘束条件の解決処理。
	btDiscreteDynamicsWorld*				m_dynamicWorld = nullptr;			//!<ワールド。
public:
	~PhysicsWorld();
	void Init();
	void Update();
	void DebubDrawWorld();
	void Release();
	/*!
	* @brief	ダイナミックワールドを取得。
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return m_dynamicWorld;
	}
	/*!
	* @brief	剛体を登録。
	*/
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	剛体を破棄。
	*/
	void RemoveRigidBody(RigidBody& rb);
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		m_dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
	void ContactText(
		btCollisionObject* colObj, 
		btCollisionWorld::ContactResultCallback& resultCallback
	)
	{
		m_dynamicWorld->contactTest(colObj, resultCallback);
	}
};

extern PhysicsWorld g_physics;


