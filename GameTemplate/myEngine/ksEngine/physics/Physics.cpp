#include "stdafx.h"
#include "physics/Physics.h"
#include "Physics/RigidBody.h"


PhysicsWorld g_physics;

PhysicsWorld::~PhysicsWorld()
{
	Release();
}
void PhysicsWorld::Release()
{
	delete m_dynamicWorld;
	delete m_constraintSolver;
	delete m_overlappingPairCache;
	delete m_collisionDispatcher;
	delete m_collisionConfig;

	m_dynamicWorld = nullptr;
	m_constraintSolver = nullptr;
	m_overlappingPairCache = nullptr;
	m_collisionDispatcher = nullptr;
	m_collisionConfig = nullptr;
}
void PhysicsWorld::Init()
{
	Release();
	//•¨—ƒGƒ“ƒWƒ“‚ð‰Šú‰»B
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	m_collisionConfig = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_collisionDispatcher = new	btCollisionDispatcher(m_collisionConfig);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	m_overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	m_constraintSolver = new btSequentialImpulseConstraintSolver;

	m_dynamicWorld = new btDiscreteDynamicsWorld(
		m_collisionDispatcher,
		m_overlappingPairCache,
		m_constraintSolver,
		m_collisionConfig
		);
	m_dynamicWorld->debugDrawWorld();
	m_dynamicWorld->setGravity(btVector3(0, -10, 0));

}
void PhysicsWorld::Update()
{
	m_dynamicWorld->stepSimulation(1.0f/60.0f);
}
void PhysicsWorld::DebubDrawWorld()
{
	m_dynamicWorld->debugDrawWorld();
}
void PhysicsWorld::AddRigidBody(RigidBody& rb)
{
	m_dynamicWorld->addRigidBody(rb.GetBody());
}
void PhysicsWorld::RemoveRigidBody(RigidBody& rb)
{
	m_dynamicWorld->removeRigidBody(rb.GetBody());
}
