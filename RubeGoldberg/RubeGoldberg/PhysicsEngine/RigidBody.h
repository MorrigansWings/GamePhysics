#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vectors.h"
#include "Matrices.h"
#include "Quaternion.h"

using namespace Physics;

class RigidBody
{
public:
	RigidBody()
		: position(Physics::Vector3(0.0f))
		, velocity(Physics::Vector3(0.0f))
		//, acceleration(Physics::Vector3(0.0f))
		//, damping(DEFAULT_DAMPING)
		//, mass(DEFAULT_MASS)
		, inverseMass((mass > 0) ? (1.0f / mass) : 0.0f) // If mass is 0, set inversemass to 0
		// SET DEFAULTS FOR ORIENTATION, ANGULAR VELOCITY AND INVERSE INERTIA TENSOR!!!
	{}

	RigidBody(	Physics::Vector3 pos, Physics::Vector3 vel, Physics::Vector3 acc,
				float damp, float ma,
				Quaternion orient, Vector3 aVel, Matrix3 invTensor)
		: position(pos)
		, velocity(vel)
		//, acceleration(acc)
		//, damping(damp)
		, mass(ma)
		, inverseMass((mass > 0) ? (1.0f / mass) : 0.0f)
		, orientation(orient)
		, angularVelocity(aVel)
		, inverseInertiaTensor(invTensor)
	{}

	~RigidBody(){};



private:
	Quaternion orientation;

	Matrix3 inverseInertiaTensor;

	Vector3 position,
			velocity,
			rotation,
			angularVelocity;

	float	mass,
			inverseMass,
			linearDamping,
			angularDamping;

	// Derived variables
	Matrix4 transform;

	Matrix3 inverseInertiaTensorWorld; //IIT in world space

	// Force and Torque Accumulators
	Vector3 forceAccum,
			torqueAccum,
			acceleration,
			lastFrameAcceleration;

};

#endif //RIGIDBODY_H