#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator()
{
	mAnchor = Vector3(0);
}

SpringForceGenerator::SpringForceGenerator(Particle* part)
{
	mEndParticle = part;
}
SpringForceGenerator::SpringForceGenerator(Vector3 anchor)
{
	mAnchor = anchor;
}

SpringForceGenerator::~SpringForceGenerator()
{}

void SpringForceGenerator::updateForce(Particle* particle, float duration)
{
	Vector3 force = particle->getPosition();

	if (mEndParticle != NULL)
		force -= mEndParticle->getPosition();
	else
		force -= mAnchor;

	float magnitude = force.magnitude();
	magnitude = fabs(magnitude - mRestLength);
	magnitude *= mK;

	force.normalize();
	force *= -magnitude;

	particle->addForce(force);
}