#include "SpringForceGenerator.h"
#include <iostream>

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
	std::cout << "SPRINGFORCEGENERATOR:updateForce: Attempting to update force!";
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