#include "GravityForceGenerator.h"

float GravityForceGenerator::GRAVITATIONAL_CONSTANT = (float)(6.673e-11);// * pow(10, -11));
float GravityForceGenerator::GAUSSIAN_CONSTANT = 0.01720209895f;
float GravityForceGenerator::EARTH_GRAVITY = 9.807; // in Newtons!

GravityForceGenerator::GravityForceGenerator()
{
	gravity = Vector3(0.0f);
	gravity.y = -EARTH_GRAVITY;
}

void GravityForceGenerator::updateForce(Particle* particle, float duration)
{
	particle->addForce(gravity * particle->getMass());
}
