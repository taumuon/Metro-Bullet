#include "pch.h"
#include "Physics.h"

#include <algorithm>

using namespace std;

Physics::Physics(void) :
	m_broadphase(new btDbvtBroadphase()),
	m_collisionConfiguration(new btDefaultCollisionConfiguration()),
	m_solver(new btSequentialImpulseConstraintSolver)
{
	m_dispatcher = std::unique_ptr<btCollisionDispatcher>(new btCollisionDispatcher(m_collisionConfiguration.get()));

	m_dynamicsWorld = std::unique_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(m_dispatcher.get(),m_broadphase.get(),m_solver.get(),m_collisionConfiguration.get()));

	m_dynamicsWorld->setGravity(btVector3(0,-10,0));
}

Physics::~Physics(void)
{
	for_each( begin(m_rigidBodies), end(m_rigidBodies), [&]( const unique_ptr<btRigidBody>& rigidBody )
	{
		m_dynamicsWorld->removeRigidBody(rigidBody.get());
		delete rigidBody->getMotionState();
	} );

	m_rigidBodies.clear();
}

void Physics::Update()
{
    m_dynamicsWorld->stepSimulation(1/60.f,10);
}

void Physics::AddPhysicalObject(btCollisionShape* collisionShape, btMotionState* motionState, btScalar mass, const btVector3& inertia)
{
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(mass, motionState,collisionShape,inertia);

	auto groundRigidBody = new btRigidBody(groundRigidBodyCI);

	m_dynamicsWorld->addRigidBody(groundRigidBody);

	m_shapes.push_back(std::unique_ptr<btCollisionShape>(collisionShape));
	m_rigidBodies.push_back(std::unique_ptr<btRigidBody>(groundRigidBody));
}
