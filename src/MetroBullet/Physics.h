#pragma once

#include <btBulletDynamicsCommon.h>

class Physics
{
public:
	Physics(void);
	~Physics(void);

	void Update();
	void AddPhysicalObject(btCollisionShape* collisionShape, btMotionState* motionState, btScalar mass, const btVector3& inertia);
private:
	Physics(const Physics&){}
	Physics& operator=(const Physics&) { return *this; }

	std::unique_ptr<btBroadphaseInterface> m_broadphase;
	std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> m_dispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
	std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

	std::vector<std::unique_ptr<btCollisionShape>> m_shapes;
	std::vector<std::unique_ptr<btRigidBody>> m_rigidBodies;
};

