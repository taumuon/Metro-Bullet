#include "pch.h"
#include "CubeMotionState.h"


CubeMotionState::CubeMotionState(Cube^ cube, const btTransform &initialTransform)
	: 
	m_cube(cube),
	m_initialTransform(initialTransform)
{
}

CubeMotionState::~CubeMotionState(void)
{
}

void CubeMotionState::getWorldTransform(btTransform &worldTransform) const
{
	worldTransform = m_initialTransform;
}

void CubeMotionState::setWorldTransform(const btTransform &worldTransform)
{
	auto rotation = worldTransform.getRotation();

	auto transform = ref new Transform(worldTransform.getOrigin().getX(),
									worldTransform.getOrigin().getY(),
									worldTransform.getOrigin().getZ(),
									rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW());

	m_cube->SetTransform(transform);
}
