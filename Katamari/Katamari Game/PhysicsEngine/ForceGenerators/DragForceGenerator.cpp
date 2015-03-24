#include "DragForceGenerator.h"

void DragForceGenerator::updateForce(Particle* particle, float duration)
{
	Vector3 velocity = particle->getVelocity();
	float drag = velocity.magnitude();
	drag = k1 * drag + k1 * drag * drag;

	Vector3 force = velocity.getNormalized();
	force *= -drag;
	particle->addForce(force);
}