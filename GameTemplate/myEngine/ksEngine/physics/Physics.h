#pragma once


class RigidBody;

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		m_collisionConfig = nullptr;
	btCollisionDispatcher*					m_collisionDispatcher = nullptr;	//!<�Փˉ��������B
	btBroadphaseInterface*					m_overlappingPairCache = nullptr;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	m_constraintSolver = nullptr;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				m_dynamicWorld = nullptr;			//!<���[���h�B
public:
	~PhysicsWorld();
	void Init();
	void Update();
	void DebubDrawWorld();
	void Release();
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return m_dynamicWorld;
	}
	/*!
	* @brief	���̂�o�^�B
	*/
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	���̂�j���B
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


