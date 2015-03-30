#include "Particle.h"

const float Particle::DEFAULT_DAMPING = 0.999f;
const float Particle::DEFAULT_MASS = 1.0f;

void Particle::integrate(float duration)
{
	// Ignore things with inverse mass
	if (inverseMass <= 0.0f) return;

	// update position
	position.addScaledVector(velocity, duration);

	// get acceleration from force
	Vector3 calculatedAcc = acceleration;
	calculatedAcc.addScaledVector(forceAccumulation, duration);

	// get linear velocity from acceleration
	velocity.addScaledVector(calculatedAcc, duration);

	// apply drag
	velocity *= pow(damping, duration);

	clearAccumulation();
}

void Particle::clearAccumulation()
{
	forceAccumulation = Vector3(0);
}

void Particle::addForce(Vector3 force)
{
	forceAccumulation += force;
}