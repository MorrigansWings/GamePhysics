#ifndef RIGIDBODY_SPRING_GENERATOR_H
#define RIGIDBODY_SPRING_GENERATOR_H

#include "RigidBodyForceGenerator.h"


class RigidBodySpringGenerator : public RigidBodyForceGenerator
{
private:
	Vector3 connectionPoint;

	Vector3 otherConnectionPoint;

	RigidBody *other;

	float springConstant;

	float restLength;

public:

	RigidBodySpringGenerator(	const Vector3 &localConnectionPt,
								RigidBody *other,
								const Vector3 &otherConnectionPt,
								float springConstant,
								float restLength)
		: connectionPoint(localConnectionPt)
		, otherConnectionPoint(otherConnectionPt)
		, other(other)
		, springConstant(springConstant)
		, restLength(restLength)
	{}

	virtual void updateForce(RigidBody *body, float duration);
};
#endif //RIGIDBODY_SPRING_GENERATOR_H