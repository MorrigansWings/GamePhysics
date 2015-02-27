#include "Particle.h"

const float Particle::DEFAULT_DAMPING = 0.999f;
const float Particle::DEFAULT_MASS = 1.0f;


void Particle::updatePosition()
{
	
}

void Particle::addForce(Vector3 force)
{
	velocity += force;
}