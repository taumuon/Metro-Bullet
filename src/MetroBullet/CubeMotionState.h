#pragma once

#include <btBulletDynamicsCommon.h>
#include "Cube.h"

class CubeMotionState : public btMotionState 
{
public:
	CubeMotionState(Cube^ cube, const btTransform &initialTransform);
	virtual ~CubeMotionState(void);

	virtual void getWorldTransform(btTransform &worldTransform) const;
	virtual void setWorldTransform(const btTransform &worldTransform);
private:
	Cube^ m_cube;
	btTransform m_initialTransform;
};

