#ifndef _RIGIDBODY_FORCE_GENERATOR_H_
#define _RIGIDBODY_FORCE_GENERATOR_H_

#include "../RigidBody.h"

using namespace Physics;

class RigidBodyForceGenerator
{
public:
	virtual void updateForce(RigidBody* body, float duration) = 0;
};

#endif //_RIGIDBODY_FORCE_GENERATOR_H_