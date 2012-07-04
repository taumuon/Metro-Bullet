#include "pch.h"
#include "Level.h"
#include "CubeMotionState.h"

Level::Level(void)
{
}

void Level::Initialise(CubeRenderer^ cubeRenderer)
{
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	auto groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	m_physics.AddPhysicalObject(groundShape, groundMotionState, 0, btVector3(0,0,0));

	for(float height=0.5f; height < 22.0f; height += 1.3f)
	{
		for(float i=-5.0f; i < 5.0f; i += 1.1f)
		{
			auto cube = cubeRenderer->CreateCube();
			m_cubes.push_back(cube);

			auto x = -height / 10.0f;
			auto y = height;
			auto z = i;

			auto fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
			btMotionState* fallMotionState = new CubeMotionState(cube, btTransform(btQuaternion(0,0,0,1),btVector3(x,y,z)));
			btScalar mass = 1;
			btVector3 fallInertia(0,0,0);
			fallShape->calculateLocalInertia(mass,fallInertia);
			m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
		}
	}
}

Level::~Level(void)
{
}

void Level::Update()
{
	m_physics.Update();
}