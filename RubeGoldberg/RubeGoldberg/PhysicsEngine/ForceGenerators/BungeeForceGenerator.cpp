#include "BungeeForceGenerator.h"

BungeeForceGenerator::BungeeForceGenerator()
{}

BungeeForceGenerator::~BungeeForceGenerator()
{}

void BungeeForceGenerator::updateForce(Particle* particle, float duration)
{
	Vector3 force = particle->getPosition();
	force -= mEndPosition->getPosition();

	float magnitude = force.magnitude();
	if (magnitude <= mRestLength)
	{
		// no force necessary - bungee is being compressed.
		return;
	}

	magnitude = mK * (magnitude - mRestLength);
	force.normalize();
	force *= -magnitude;

	particle->addForce(force);
}