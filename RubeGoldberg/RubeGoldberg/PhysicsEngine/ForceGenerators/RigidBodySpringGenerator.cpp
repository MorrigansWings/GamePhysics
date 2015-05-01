#include "RigidBodySpringGenerator.h"

void RigidBodySpringGenerator::updateForce(RigidBody* body, float duration)
{
	// Calculate the two ends in world space
	Vector3 lws = body->convertPointToWorldSpace(connectionPoint);
	Vector3 ows = other->convertPointToWorldSpace(otherConnectionPoint);

	// Calculate the vector of the spring
	Vector3 force = lws - ows;

	// Calculate the magnitude of the force
	float magnitude = force.magnitude();
	magnitude = abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force.normalize();
	force *= -magnitude;
	body->addForceAtPoint(force, lws);
}