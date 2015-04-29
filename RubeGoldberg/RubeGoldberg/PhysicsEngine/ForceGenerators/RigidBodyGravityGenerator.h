#ifndef _RIGIDBODY_GRAVITY_FORCE_GENERATOR_H_
#define _RIGIDBODY_GRAVITY_FORCE_GENERATOR_H_

#include "RigidBodyForceGenerator.h"

using namespace Physics;

class RigidBodyGravityGenerator : public RigidBodyForceGenerator
{
public:
	static float EARTH_GRAVITY;
	RigidBodyGravityGenerator();
	RigidBodyGravityGenerator(float scalar);
	virtual void updateForce(RigidBody* body, float duration);
private:
	Vector3 gravity;
};


#endif // _RIGIDBODY_GRAVITY_FORCE_GENERATOR_H_